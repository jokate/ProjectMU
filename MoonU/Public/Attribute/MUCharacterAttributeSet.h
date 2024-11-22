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
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, MaxExperience);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentExperience);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected :

#pragma region Experience
	
	UPROPERTY(BlueprintReadWrite, Category = "Experience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxExperience;

	UPROPERTY(BlueprintReadWrite, Category = "Experience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentExperience;

#pragma endregion Experience
};
