// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "MUCharacterBase.h"
#include "Interface/MUEnemy.h"
#include "MUCharacterNonPlayer.generated.h"

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

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue) override;
	
protected :
	UPROPERTY()
	TObjectPtr<class UMUCharacterAttributeSetBase> AttributeSet;

	UPROPERTY()
	TObjectPtr<class UTimeStopComponent> TimeStopComponent;
};
