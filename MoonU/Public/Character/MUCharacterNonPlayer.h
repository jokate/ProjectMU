// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/TimerWindTarget.h"
#include "MUCharacterNonPlayer.generated.h"

UCLASS()
class MOONU_API AMUCharacterNonPlayer : public ACharacter, public IAbilitySystemInterface, public ITimeWindTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterNonPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetTimeWind(bool InTimeWind) override;

	virtual const bool GetTimeWind() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAbilityInitComponent> AbilityInitComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeWindComponent> TimeWindComponent;
};
