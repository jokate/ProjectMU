// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSetBase.h"
#include "MUTimewinderAttribute.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUTimewinderAttribute : public UAttributeSet
{
	
	GENERATED_BODY()

public :
	UMUTimewinderAttribute();
	
	ATTRIBUTE_ACCESSORS(UMUTimewinderAttribute, CurrentTimeGauge);
	ATTRIBUTE_ACCESSORS(UMUTimewinderAttribute, MaxTimeGauge);
	ATTRIBUTE_ACCESSORS(UMUTimewinderAttribute, TimewindConsumption);
	ATTRIBUTE_ACCESSORS(UMUTimewinderAttribute, TimeStopConsumption);
	ATTRIBUTE_ACCESSORS(UMUTimewinderAttribute, TimeStopDuration);

protected :
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	//캐릭터 별로 생성 및 붙여야 하는 Attribute의 수에 따른 부분.
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
