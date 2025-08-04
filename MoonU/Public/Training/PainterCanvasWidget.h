// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NNERuntimeCPU.h"
#include "Blueprint/UserWidget.h"
#include "PainterCanvasWidget.generated.h"

class UCanvasRenderTarget2D;
class UButton;
class UCanvasWidget;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCanvasButtonPressed );

UCLASS()
class MOONU_API UPainterCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

public : 
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	UFUNCTION()
	virtual void OnPaintButtonPressed();

	UFUNCTION()
	virtual void DrawToCanvas( UCanvas* Canvas, int32 Width, int32 Height );

	UFUNCTION()
	virtual UCanvasRenderTarget2D* GetRenderTarget() { return RenderTarget; }
	
public :
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UCanvasWidget> CanvasWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> PaintButton;

	UPROPERTY( BlueprintAssignable )
	FOnCanvasButtonPressed OnCanvasButtonPressed;
	
	UPROPERTY( EditAnywhere )
	TObjectPtr<UNNEModelData> PreloadedModelData;

	UPROPERTY()
	TObjectPtr<UCanvasRenderTarget2D> RenderTarget;
	
private :// 	https://dev.epicgames.com/community/learning/courses/e7w/unreal-engine-neural-network-engine-nne/34q9/unreal-engine-nne-quick-start-guide-5-3
	TUniquePtr<UE::NNE::IModelInstanceCPU> ModelInstance;
	TArray<float> InputData;
	TArray<float> OutputData;
	TArray<UE::NNE::FTensorBindingCPU> InputBindings;
	TArray<UE::NNE::FTensorBindingCPU> OutputBindings;
	bool bIsRunning = false;
	
};
