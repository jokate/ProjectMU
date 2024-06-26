﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnum.h"
#include "GameplayTagContainer.h"
#include "Data/MUEnum.h"
#include "Perception/AIPerceptionTypes.h"
#include "MUAIController.generated.h"

UCLASS()
class MOONU_API AMUAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAIController();

	void RunAI();

	void StopAI();

	virtual void OnInitialize();
	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus);

#pragma region IGenericTeamAgentInteface
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
#pragma endregion 
	
protected :
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<class UAISense>, FName> KeyForBlackboard;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBehaviorTree> BTAsset;


	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECharacterType> CharacterType;
};
