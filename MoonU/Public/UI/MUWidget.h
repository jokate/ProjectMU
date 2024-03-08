// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UI/Widget/MUWidgetInterface.h"
#include "MUWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUWidget : public UUserWidget, public IMUWidgetInterface
{
	GENERATED_BODY()

public :
	virtual void OnWidgetShow() override;

	virtual void OnWidgetHide() override;

	virtual void OnWidgetUpdated() override;
	
	virtual void OnWidgetUpdatedByActor(AActor* InActor) override;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetShow_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetHide_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetUpdated_BP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetUpdatedByActor_BP(AActor* InActor);
};
