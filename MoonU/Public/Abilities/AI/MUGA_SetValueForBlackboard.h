// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AI/AIEnum.h"
#include "MUGA_SetValueForBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_SetValueForBlackboard : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_SetValueForBlackboard();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void TryChangeBlackboardValue();

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FName SelectedKey;
	
	UPROPERTY(EditAnywhere, Category = ValueSetter)
	TEnumAsByte<EBlackboardKeyData> DataTypeToChange;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	float ChangeValFloat;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	int32 ChangeValInt;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FVector ChangeValVector;
	
	UPROPERTY(EditAnywhere, Category = ValueSetter)
	bool ChangeValBool;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FName EnumName;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FName EnumValue;
};
