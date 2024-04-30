// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MUAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AI/MUAIDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	OnInitialize();
}

void AMUAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BTComponent)
	{
		BTComponent->StopTree();
	}

	PerceptionComponent->OnTargetPerceptionUpdated.RemoveAll(this);
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

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMUAIController::OnTargetPerceptionUpdated);
}

void AMUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
	
	SetGenericTeamId(FGenericTeamId(CharacterType));
}

void AMUAIController::OnTargetPerceptionUpdated(AActor* InActor, FAIStimulus Stimulus)
{
	if (InActor == nullptr)
	{
		return;
	}

	if (InActor == GetPawn())
	{
		return;
	}
	
	TSubclassOf<UAISense> CurrentSense = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);

	if (CurrentSense == nullptr)
	{
		return;
	}

	if (KeyForBlackboard.Contains(CurrentSense) == false)
	{
		return;
	}

	const bool CurrentValue = Stimulus.WasSuccessfullySensed();
	const FName KeyName = KeyForBlackboard[CurrentSense];
	
	Blackboard->SetValueAsBool(KeyName, CurrentValue);	
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



