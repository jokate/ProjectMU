// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSetBase.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MOONU_API UMUCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, Damage);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, CurrentHp);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, MaxHp);
	
public :
	UMUCharacterAttributeSetBase();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
protected :
	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "HP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHp;

	UPROPERTY(BlueprintReadOnly, Category = "HP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHp;
};
