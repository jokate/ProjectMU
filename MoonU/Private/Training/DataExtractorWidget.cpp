// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonU/Public/Training/DataExtractorWidget.h"

#include "HighResScreenshot.h"
#include "ImageUtils.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Engine/DataTable.h"
#include "Training/CanvasWidget.h"
#include "Data/MUStruct.h"

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

	if ( IsValid(ExtractButton) == true )
	{
		ExtractButton->OnClicked.AddDynamic( this, &UDataExtractorWidget::SaveCanvas );
	}

	if ( IsValid( ResetButton ) == true )
	{
		ResetButton->OnClicked.AddDynamic( this, &UDataExtractorWidget::ResetIndex );
	}
}

int32 UDataExtractorWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if ( IsValid( CanvasRenderTarget ) == true )
	{
		CanvasRenderTarget->UpdateResource();	
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UDataExtractorWidget::DrawToCanvas(UCanvas* Canvas, int32 Width, int32 Height)
{
	if ( IsValid( CanvasWidget ) == false )
	{
		return;
	}
	
	FLinearColor TransparentColor = FLinearColor::White;
	
	Canvas->K2_DrawBox(FVector2D(0, 0), FVector2D(Width, Height), 0, TransparentColor);

	for ( const FDrawingCoordinate& Coords : CanvasWidget->GetAllCoordinate() )
	{
		const TArray<FVector2D>& Coordinate = Coords.Coordinates;

		for (int32 i = 0; i < Coordinate.Num() - 1; ++i)
		{
			Canvas->K2_DrawLine(Coordinate[i], Coordinate[i + 1], 10.f, FLinearColor::White);
		}
	}
}

void UDataExtractorWidget::SaveCanvas()
{
	FTextureRenderTargetResource* RTResource = CanvasRenderTarget->GameThread_GetRenderTargetResource();

	TArray<FColor> OutBMP;
	RTResource->ReadPixels(OutBMP);
	
	FIntPoint DestSize(RTResource->GetSizeX(), RTResource->GetSizeY());

	TArray64<uint8> CompressedPNG;
	FImageUtils::PNGCompressImageArray(DestSize.X, DestSize.Y, OutBMP, CompressedPNG);
	
	
	FString FilePath = FPaths::ProjectSavedDir() / 	FString::Printf( TEXT("Pattern/Pattern%s_%d.png"), *SignNumber->GetText().ToString(), Index++);
	FFileHelper::SaveArrayToFile(CompressedPNG, *FilePath);

	if ( IsValid( CanvasWidget) == true )
	{
		CanvasWidget->ResetAllMember();
	}
}
