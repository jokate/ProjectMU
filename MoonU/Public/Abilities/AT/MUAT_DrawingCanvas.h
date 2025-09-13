// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAT_ActivateTagWidget.h"
#include "NNEModelData.h"
#include "NNERuntimeCPU.h"
#include "MUAT_DrawingCanvas.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCanvasDrawingComplete, const TArray<float>&, Output );

UCLASS()
class MOONU_API UMUAT_DrawingCanvas : public UMUAT_ActivateTagWidget
{
	GENERATED_BODY()

public :
	static UMUAT_DrawingCanvas* CreateDrawingCanvas( UGameplayAbility* GameplayAbility, UNNEModelData* ModelData, FGameplayTag InWidgetTag );

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	UFUNCTION()
	void ProcessModelRun();

protected :
	virtual void ProcessData();
	virtual void RunModel();
	
public :
	UPROPERTY( EditAnywhere )
	TWeakObjectPtr<UNNEModelData> PreloadedModelData;

	UPROPERTY( BlueprintAssignable )
	FOnCanvasDrawingComplete OnCanvasDrawingComplete;
	
private :
	// 	https://dev.epicgames.com/community/learning/courses/e7w/unreal-engine-neural-network-engine-nne/34q9/unreal-engine-nne-quick-start-guide-5-3
	TSharedPtr<UE::NNE::IModelInstanceCPU> ModelInstance;
	TArray<float> InputData;
	TArray<float> OutputData;
	TArray<UE::NNE::FTensorBindingCPU> InputBindings;
	TArray<UE::NNE::FTensorBindingCPU> OutputBindings;
};
