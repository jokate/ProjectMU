// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataExtractorWidget.generated.h"

class UCanvasRenderTarget2D;
/**
 * 
 */
USTRUCT( BlueprintType )
struct FDrawingCoordinate
{
	GENERATED_BODY()

public :
	UPROPERTY( BlueprintReadOnly )
	TArray<FVector2D> Coordinates;
};

class UDataTable;
UCLASS()
class MOONU_API UDataExtractorWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;

	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void ResetAllMember();

	UFUNCTION()
	virtual void DrawToCanvas( UCanvas* Canvas, int32 Width, int32 Height );

	virtual void SaveCanvas();
public :
	UPROPERTY( BlueprintReadOnly )
	TArray<FDrawingCoordinate> CoordinatesArray;
	
	UPROPERTY()
	TObjectPtr<UCanvasRenderTarget2D> CanvasRenderTarget;

	UPROPERTY( BlueprintReadOnly )
	int32 MouseIndex = 0;

	UPROPERTY( BlueprintReadOnly )
	bool bMousePressed = false;
};
