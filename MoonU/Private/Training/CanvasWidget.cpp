// Fill out your copyright notice in the Description page of Project Settings.


#include "Training/CanvasWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Data/MUStruct.h"

void UCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FVector2D LocalVector = UWidgetLayoutLibrary::GetViewportSize(this);
}

void UCanvasWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

int32 UCanvasWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FPaintContext PaintContext( AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled );

	for ( const FDrawingCoordinate& Coords : CoordinatesArray )
	{
		UWidgetBlueprintLibrary::DrawLines( PaintContext, Coords.Coordinates, FLinearColor::Blue, true, 10);
	}

	return LayerId + 1;
}

FReply UCanvasWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if ( InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton )
	{
		bMousePressed = true;
	}
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UCanvasWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if ( InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton )
	{
		bMousePressed = false;
		++MouseIndex;
	}
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UCanvasWidget::ResetAllMember()
{
	bMousePressed = false;
	CoordinatesArray.Empty();
	MouseIndex = 0;
}
