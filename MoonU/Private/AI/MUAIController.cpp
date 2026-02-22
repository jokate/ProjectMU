// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MUAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "StateTree.h"
#include "AI/MUAIDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/EQSActivationComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/StateTreeAIComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
AMUAIController::AMUAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>("StateTreeComponent");
}

void AMUAIController::RunAI()
{
	OnInitialize();
}

void AMUAIController::StopAI()
{
	StateTreeAIComponent->StopLogic(TEXT("StopAI"));
}

void AMUAIController::OnInitialize()
{
	StateTreeAIComponent->StartLogic();
}

void AMUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
	
	SetGenericTeamId(FGenericTeamId(CharacterType));
}

void AMUAIController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

ETeamAttitude::Type AMUAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn))
		{
			const FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

			if (OtherTeamID.GetId() == ECharacterType::Neutral)
			{
				return ETeamAttitude::Neutral;
			}
			
			if (OtherTeamID.GetId() != GetGenericTeamId())
			{
				return ETeamAttitude::Hostile;
			}

			return ETeamAttitude::Friendly;
		}
	}

	return ETeamAttitude::Neutral;
}



