// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "MUCharacterBase.h"
#include "Interface/MUEnemy.h"
#include "Interface/TargetManager.h"
#include "MUCharacterNonPlayer.generated.h"

struct FGameplayEventData;

UCLASS()
class MOONU_API AMUCharacterNonPlayer : public AMUCharacterBase, public IMUEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterNonPlayer();

	virtual void OnDead(const FGameplayEventData* Data);
protected:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;

	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue) override;

#pragma region ITargetManager
	virtual bool IsTargetValid() const override;

	virtual AActor* GetActorTarget() const override;
	
	virtual void SetupTarget(AActor* NewTarget) override;

	virtual FVector GetTargetLocation() const override;
	
	virtual void SetupTargetLocation(FVector NewTargetLocation) override;
#pragma endregion
	
protected :
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTargetManagingComponent> TargetManagingComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTimeStopComponent> TimeStopComponent;
};
