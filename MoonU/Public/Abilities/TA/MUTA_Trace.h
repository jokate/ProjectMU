// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "MUTA_Trace.generated.h"

//Notify State가 진행됨에 따라서 Trace를 계속해서 수행할 Actor.
UCLASS()
class MOONU_API AMUTA_Trace : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTA_Trace();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual FGameplayAbilityTargetDataHandle MakeTargetData();

	virtual void ConfirmTargetingAndContinue() override;
	
	virtual void OnAnimNotifyStateEnd(const FGameplayEventData* EventData);

	virtual void TraceStart();

	virtual void SetComboData(int32 Combo);

protected:
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> QueryActors;

	UPROPERTY()
	int32 CurrentCombo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> DamageEffectClass;
};
