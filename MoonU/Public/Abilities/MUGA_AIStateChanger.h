// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
#include "Perception/AIPerceptionTypes.h"
#include "MUGA_AIStateChanger.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIStateChanger : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_AIStateChanger();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	virtual void OnUpdatePerceptions(const TArray<AActor*>& UpdatedActors);

	virtual void HandleEventByPerceptionType(EPerceptionType Type, bool bPerceptionIsActive);

public :
	UFUNCTION(BlueprintImplementableEvent)
	void OnPerceptionTypeHandle_BP(EPerceptionType InType, const AActor* UpdatedActor, const FAIStimulus& Stimulus);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class AAIController> CachedAIController;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<class UAISense>,TEnumAsByte<EPerceptionType>> PerceptionType;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EPerceptionType>, FGameplayTag> ActivateTagByPerceptions;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EPerceptionType>, FGameplayTag> DeactivateTagByPerceptions;
};
