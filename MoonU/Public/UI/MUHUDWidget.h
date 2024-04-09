// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGASWidget.h"
#include "MUWidget.h"
#include "MUHUDWidget.generated.h"

struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS()
class MOONU_API UMUHUDWidget : public UMUGASWidget
{
	GENERATED_BODY()

public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;
protected :
	virtual void OnStaminaChanged(const FOnAttributeChangeData& ChangeData);

protected :
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged_BP(float CurrentStamina);
};
