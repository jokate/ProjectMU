// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MUAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AI/MUAIDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MUCharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

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

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMUAIController::OnTargetPerceptionUpdated);

	OnInitialize();
}

void AMUAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AMUAIController::OnInitialize()
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());

	if (ASC == nullptr)
	{
		return;

	}

	const UMUCharacterAttributeSetBase* AttributeSet = ASC->GetSet<UMUCharacterAttributeSetBase>();

	if (AttributeSet == nullptr)
	{
		return;
	}

	if (Blackboard)
	{
		Blackboard->SetValueAsFloat(MU_AI_ATTACK_RADIUS, AttributeSet->GetAttackRange());
		Blackboard->SetValueAsFloat(MU_AI_DEFEND_RADIUS, AttributeSet->GetDefendRange());
	}	
}

void AMUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
}

void AMUAIController::OnTargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
	if (InActor == GetPawn())
	{
		return;
	}
	
	const bool bIsCharacter = InActor->IsA(AMUCharacterBase::StaticClass());

	if (!bIsCharacter)
	{
		return;
	}

	TSubclassOf<UAISense> CurrentSense = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);

	if (CurrentSense == nullptr)
	{
		return; 
	}
	
	//Blackboard에 데이터에 관한 주입을 진행한다.
	SetBlackboardValue(InActor, Stimulus);

	//태그를 전송한다.
	if (Stimulus.WasSuccessfullySensed())
	{
		if (StartTagByPerceptions.Contains(CurrentSense))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), StartTagByPerceptions[CurrentSense], FGameplayEventData());	
		}
	}
	else
	{
		if (EndTagByPerceptions.Contains(CurrentSense))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), EndTagByPerceptions[CurrentSense], FGameplayEventData());
		}
	}
	
}

void AMUAIController::SetBlackboardValue(AActor* InActor, const FAIStimulus& Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() == false)
	{
		return;
	}
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	if (BlackboardComponent == nullptr)
	{
		return;
	}
	
	BlackboardComponent->SetValueAsObject(MU_AI_TARGET, InActor);
	BlackboardComponent->SetValueAsVector( MU_AI_INTEREST_POINT, Stimulus.StimulusLocation);
	
}


