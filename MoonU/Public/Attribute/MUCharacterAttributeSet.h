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
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentTimeGauge);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, MaxTimeGauge);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, TimewindConsumption);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, TimeStopConsumption);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, TimeStopDuration);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, MaxExperience);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentExperience);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSet, CurrentLevel);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected :
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

#pragma region Experience
	UPROPERTY(BlueprintReadWrite, Category = "Experience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxExperience;

	UPROPERTY(BlueprintReadWrite, Category = "Experience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentExperience;

	UPROPERTY(BlueprintReadWrite, Category = "Experience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentLevel;

#pragma endregion Experience
	
	UPROPERTY(BlueprintReadOnly, Category = "Time Gauge", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentTimeGauge;

	UPROPERTY(BlueprintReadOnly, Category = "Time Gauge", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxTimeGauge;

	UPROPERTY(BlueprintReadOnly, Category = "Time Wind Consumption")
	FGameplayAttributeData TimewindConsumption;

	UPROPERTY(BlueprintReadOnly, Category = "Time Stop Consmuption")
	FGameplayAttributeData TimeStopConsumption;

	UPROPERTY(BlueprintReadOnly, Category = "Time Stop Duration")
	FGameplayAttributeData TimeStopDuration;
};
