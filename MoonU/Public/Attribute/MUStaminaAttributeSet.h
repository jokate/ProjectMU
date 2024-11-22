// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSetBase.h"
#include "MUStaminaAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUStaminaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :

	UMUStaminaAttributeSet();
	
	ATTRIBUTE_ACCESSORS(UMUStaminaAttributeSet, CurrentStamina);
	ATTRIBUTE_ACCESSORS(UMUStaminaAttributeSet, MaxStamina);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
protected :
		
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;
};
