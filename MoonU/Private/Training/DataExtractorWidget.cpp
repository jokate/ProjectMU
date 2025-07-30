// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonU/Public/Training/DataExtractorWidget.h"

#include "HighResScreenshot.h"
#include "ImageUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Engine/DataTable.h"

/*void UDataExtractorWidget::AddRowForTrainingInfo(UDataTable* InfoDataTable, FName InRowName, FString FileName)
{
	if (IsValid(InfoDataTable) == false)
	{
		return;
	}

	/*FTrainingDataTable* TrainingData = InfoDataTable->FindRow<FTrainingDataTable>(InRowName, "");

	if (TrainingData == nullptr)
	{
		return;
	}

	FTrainingDataTable TmpTrainingData = *TrainingData;

	TmpTrainingData.FileString.Add(FileName);

	InfoDataTable->AddRow(InRowName, TmpTrainingData);#1#
}*/

void UDataExtractorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FVector2D LocalVector = UWidgetLayoutLibrary::GetViewportSize(this);
	CanvasRenderTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D( this, UCanvasRenderTarget2D::StaticClass(), LocalVector.X, LocalVector.Y );
	CanvasRenderTarget->OnCanvasRenderTargetUpdate.AddDynamic( this, &UDataExtractorWidget::DrawToCanvas );
}

void UDataExtractorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if ( bMousePressed )
	{
		if ( CoordinatesArray.IsValidIndex(MouseIndex) == false )
		{
			FDrawingCoordinate DrawingCoordinate;
			CoordinatesArray.Add(DrawingCoordinate);
		}

		FDrawingCoordinate& TempDrawing = CoordinatesArray[MouseIndex];
		FVector2D CurrentCoord = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		TempDrawing.Coordinates.Emplace(CurrentCoord);
	}
}

int32 UDataExtractorWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FPaintContext PaintContext( AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );

	for ( const FDrawingCoordinate& Coords : CoordinatesArray )
	{
		UWidgetBlueprintLibrary::DrawLines( PaintContext, Coords.Coordinates, FLinearColor::Blue, true, 10);
	}

	if ( IsValid(CanvasRenderTarget) )
	{
		CanvasRenderTarget->UpdateResource();
	}

	return LayerId + 1;
}

FReply UDataExtractorWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if ( InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton )
	{
		bMousePressed = true;
	}
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UDataExtractorWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if ( InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton )
	{
		bMousePressed = false;
		++MouseIndex;
	}
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UDataExtractorWidget::ResetAllMember()
{
	bMousePressed = false;
	CoordinatesArray.Empty();
	MouseIndex = 0;

	SaveCanvas();
}

void UDataExtractorWidget::DrawToCanvas(UCanvas* Canvas, int32 Width, int32 Height)
{
	FLinearColor TransparentColor = FLinearColor::White;
	
	Canvas->K2_DrawBox(FVector2D(0, 0), FVector2D(Width, Height), 0, TransparentColor);

	for ( const FDrawingCoordinate& Coords : CoordinatesArray )
	{
		const TArray<FVector2D>& Coordinate = Coords.Coordinates;

		for (int32 i = 0; i < Coordinate.Num() - 1; ++i)
		{
			Canvas->K2_DrawLine(Coordinate[i], Coordinate[i + 1], 10.f, FLinearColor::Blue);
		}
	}
}

void UDataExtractorWidget::SaveCanvas()
{
	FTextureRenderTargetResource* RTResource = CanvasRenderTarget->GameThread_GetRenderTargetResource();

	TArray<FColor> OutBMP;
	RTResource->ReadPixels(OutBMP);

	// PNG 저장
	FIntPoint DestSize(RTResource->GetSizeX(), RTResource->GetSizeY());

	TArray64<uint8> CompressedPNG;
	FImageUtils::PNGCompressImageArray(DestSize.X, DestSize.Y, OutBMP, CompressedPNG);

	FString FilePath = FPaths::ProjectSavedDir() / TEXT("DrawnImage.png");
	FFileHelper::SaveArrayToFile(CompressedPNG, *FilePath);
}
