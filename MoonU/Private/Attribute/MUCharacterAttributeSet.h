// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class MOONU_API UMUCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UMUCharacterAttributeSet();
public :
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentStamina);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, MaxStamina);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

protected :
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;
};
