// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MUAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Interface/MUPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

// Sets default values
AMUAIController::AMUAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void AMUAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();

	bool bUseBlackBoard = UseBlackboard(BBAsset, BlackboardComp);

	if (bUseBlackBoard)
	{
		RunBehaviorTree(BTAsset);
	}
}

void AMUAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
	//Test Code
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMUAIController::InitTestCode, 0.2f, false);
}

void AMUAIController::InitTestCode()
{
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	
	if (BlackboardComponent)
	{
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		BlackboardComponent->SetValueAsObject(MU_AI_TARGET, Player);
	}
}

void AMUAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (const auto* UpdatedActor : UpdatedActors)
	{
		const FActorPerceptionInfo* ActorPerceptionInfo = PerceptionComponent->GetActorInfo(*UpdatedActor);		
		TArray<FAIStimulus> CurrentStimuluses = ActorPerceptionInfo->LastSensedStimuli;


		for (const auto& CurrentStimulus : CurrentStimuluses)
		{
			TSubclassOf<UAISense> AISense = UAIPerceptionSystem::GetSenseClassForStimulus(this, CurrentStimulus);
			
			if (PerceptionType.Contains(AISense))
			{
				const EPerceptionType Perception = PerceptionType[AISense];
				
				HandleEventByPerceptionType(Perception, CurrentStimulus.IsActive());
				OnPerceptionTypeHandle_BP(Perception, CurrentStimulus);
			}
		}
	}
}

void AMUAIController::HandleEventByPerceptionType(EPerceptionType Type, bool bIsActive)
{
	if (ValByPerceptions.Contains(Type) == false)
	{
		return;
	}
	
	const FGameplayTag& CharacterTag = ValByPerceptions[Type];
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());

	if (bIsActive)
	{
		if (ASC->HasMatchingGameplayTag(CharacterTag) == false)
		{
			ASC->AddLooseGameplayTag(CharacterTag);
		}
	}
	else
	{
		if (ASC->HasMatchingGameplayTag(CharacterTag))
		{
			ASC->RemoveLooseGameplayTag(CharacterTag);
		}
	}
}


