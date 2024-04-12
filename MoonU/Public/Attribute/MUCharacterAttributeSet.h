// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSetBase.h"
#include "MUCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUCharacterAttributeSet : public UMUCharacterAttributeSetBase
{
	GENERATED_BODY()

	UMUCharacterAttributeSet();
public :
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentStamina);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, MaxStamina);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected :
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;
};
