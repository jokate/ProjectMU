// Fill out your copyright notice in the Description page of Project Settings.


#include "Training/PainterCanvasWidget.h"

#include "ImageUtils.h"
#include "NNE.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Data/MUStruct.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Training/CanvasWidget.h"
void UPainterCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(PaintButton) )
	{
		PaintButton->OnClicked.AddDynamic( this, &UPainterCanvasWidget::OnPaintButtonPressed );
	}

	RenderTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D( this, UCanvasRenderTarget2D::StaticClass(), 256, 256 );
	RenderTarget->OnCanvasRenderTargetUpdate.AddDynamic( this, &UPainterCanvasWidget::DrawToCanvas );
}

int32 UPainterCanvasWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if ( IsValid( RenderTarget ) == true )
	{
		RenderTarget->UpdateResource();	
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UPainterCanvasWidget::OnPaintButtonPressed()
{
	if ( OnCanvasButtonPressed.IsBound() == true )
	{
		OnCanvasButtonPressed.Broadcast();
	}
	
	if ( IsValid(CanvasWidget) )
	{
		CanvasWidget->ResetAllMember();
	}
}

void UPainterCanvasWidget::DrawToCanvas(UCanvas* Canvas, int32 Width, int32 Height)
{
	if (!IsValid(CanvasWidget))
	{
		return;
	}

	FVector2D CanvasSize = FVector2D(Width, Height); 
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize( this ) / UWidgetLayoutLibrary::GetViewportScale( this );

	
	Canvas->K2_DrawBox(FVector2D(0, 0), CanvasSize, 0.f, FLinearColor::White);

	for (const FDrawingCoordinate& Coords : CanvasWidget->GetAllCoordinate())
	{
		const TArray<FVector2D>& Coordinate = Coords.Coordinates;

		for (int32 i = 0; i < Coordinate.Num() - 1; ++i)
		{
			FVector2D StartViewport = Coordinate[i] * 256;
			StartViewport.X = StartViewport.X / ViewportSize.X;
			StartViewport.Y = StartViewport.Y / ViewportSize.Y;
			
			FVector2D EndViewport = Coordinate[i + 1] * 256;
			EndViewport.X = EndViewport.X / ViewportSize.X;
			EndViewport.Y = EndViewport.Y / ViewportSize.Y;

			// 선 그리기
			Canvas->K2_DrawLine(StartViewport, EndViewport, 1.f, FLinearColor::White);
		}
	}
}
