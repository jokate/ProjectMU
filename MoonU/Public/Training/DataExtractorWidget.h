// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataExtractorWidget.generated.h"

class UCanvasWidget;
class UCanvasRenderTarget2D;
/**
 * 
 */
class UDataTable;
class UButton;

UCLASS()
class MOONU_API UDataExtractorWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	UFUNCTION()
	virtual void DrawToCanvas( UCanvas* Canvas, int32 Width, int32 Height );

	UFUNCTION()
	virtual void SaveCanvas();

public :
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UCanvasWidget> CanvasWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> ExtractButton;
	
	UPROPERTY()
	TObjectPtr<UCanvasRenderTarget2D> CanvasRenderTarget;
};
