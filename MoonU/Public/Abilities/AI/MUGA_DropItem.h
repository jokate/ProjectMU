// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_DropItem.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_DropItem : public UGameplayAbility
{
	GENERATED_BODY()
	
public :
	UMUGA_DropItem();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Drop ID")
	FName ItemDropName;
};
