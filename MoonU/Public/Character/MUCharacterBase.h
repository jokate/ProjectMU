// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/TimerWindTarget.h"
#include "MUCharacterBase.generated.h"

UCLASS()
class MOONU_API AMUCharacterBase : public ACharacter, public ITimeWindTarget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
#pragma region ITimeWindTarget
	virtual void SetTimeWind(bool InTimeRewind) override;
	virtual const bool GetTimeWind() override;
#pragma endregion

#pragma region IMotionWarpTarget
	virtual class UMotionWarpingComponent* GetMotionWarpComponent(); 
	
	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f);

	virtual void ReleaseMotionWarp(const FName InName);
#pragma endregion
	
protected :
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Warping")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability Init Component")
	TObjectPtr<class UAbilityInitComponent> AbilityInitComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time Wind Component")
	TObjectPtr<class UTimeWindComponent> TimeWindComponent;
};
