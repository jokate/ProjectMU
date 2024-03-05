// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MUHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UFUNCTION(BlueprintImplementableEvent)
	void OnOxygenChanged_BP(float InOxygen);

	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged_BP(float InStamina);
};
