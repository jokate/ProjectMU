// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UI/Widget/HUDWidgetInterface.h"
#include "MUHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUHUDWidget : public UUserWidget, public IHUDWidgetInterface
{
	GENERATED_BODY()

	virtual void OnOxygenChanged(float InOxygen) override;

	virtual void OnStaminaChanged(float InStamina) override;

	virtual void OnInteratableObjectInBound(AActor* InteractableActor) override;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnOxygenChanged_BP(float InOxygen);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged_BP(float InStamina);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteratableObjectInBound_BP(AActor* InteractableActor);
};
