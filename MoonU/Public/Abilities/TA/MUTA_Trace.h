// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Abilities/GameplayAbilityTypes.h"
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
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	virtual FGameplayAbilityTargetDataHandle MakeTargetData();

	virtual void ConfirmTargetingAndContinue() override;
	
	virtual void OnAnimNotifyStateEnd(const FGameplayEventData* EventData);

	virtual void TraceStart();

	virtual void InitializeData(const FName& InTargetDamageInfo);

	virtual void ProcessHitResult(const TArray<FHitResult>& HitResults);

	virtual void ProcessDamage(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC);

	virtual void ApplyBuff(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC, TSubclassOf<UGameplayEffect> BuffEffectClass );

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MUTA")
	TObjectPtr<USceneComponent> RootCollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MUTA")
	FName WeaponSocketName = NAME_None;

	UPROPERTY()
	TArray<UShapeComponent*> DamageShapes;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> QueryActors;

	UPROPERTY()
	FName TargetDamageInfo;
};
