// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AIStateChanger.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "AI/MUAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

UMUGA_AIStateChanger::UMUGA_AIStateChanger()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AIStateChanger::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();

	if (AvatarActor == nullptr)
	{
		return;
	}

	ACharacter* AICharacter = Cast<ACharacter>(AvatarActor);

	if (AICharacter == nullptr)
	{
		return;
	}
	AMUAIController* AIController = Cast<AMUAIController>(UAIBlueprintHelperLibrary::GetAIController(AICharacter));

	if (AIController == nullptr)
	{
		return;
	}

	CachedAIController = AIController;

	if (auto* PerceptionComp = CachedAIController->GetPerceptionComponent())
	{
		PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &UMUGA_AIStateChanger::OnUpdatePerceptions);	
	}
}

void UMUGA_AIStateChanger::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (CachedAIController == nullptr)
	{
		return;
	}
	
	if (auto* PerceptionComp = CachedAIController->GetPerceptionComponent())
	{
		PerceptionComp->OnPerceptionUpdated.RemoveDynamic(this, &UMUGA_AIStateChanger::OnUpdatePerceptions);	
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UMUGA_AIStateChanger::OnUpdatePerceptions(const TArray<AActor*>& UpdatedActors)
{
	if (CachedAIController == nullptr)
	{
		return;
	}
	
	const auto& PerceptionComp = CachedAIController->PerceptionComponent;

	if (PerceptionComp == nullptr)
	{
		return;
	}
	
	for (const auto* UpdatedActor : UpdatedActors)
	{
		const FActorPerceptionInfo* ActorPerceptionInfo = PerceptionComp->GetActorInfo(*UpdatedActor);		
		const TArray<FAIStimulus>& CurrentStimuluses = ActorPerceptionInfo->LastSensedStimuli;


		for (const auto& CurrentStimulus : CurrentStimuluses)
		{
			TSubclassOf<UAISense> AISense = UAIPerceptionSystem::GetSenseClassForStimulus(CachedAIController, CurrentStimulus);
			
			if (PerceptionType.Contains(AISense))
			{
				const EPerceptionType Perception = PerceptionType[AISense];
				HandleEventByPerceptionType(Perception, CurrentStimulus.IsActive());
				OnPerceptionTypeHandle_BP(Perception, UpdatedActor, CurrentStimulus);
			}
		}
	}
}

void UMUGA_AIStateChanger::HandleEventByPerceptionType(EPerceptionType Type, bool bPerceptionIsActive)
{
	if (ValByPerceptions.Contains(Type) == false)
	{
		return;
	}
	
	const FGameplayTag& CharacterTag = ValByPerceptions[Type];
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentActorInfo->AvatarActor.Get());

	if (bPerceptionIsActive)
	{
		if (ASC->HasMatchingGameplayTag(CharacterTag) == false)
		{
			ASC->AddLooseGameplayTag(CharacterTag);
		}
	}
	else
	{
d		if (ASC->HasMatchingGameplayTag(CharacterTag))
		{
			ASC->RemoveLooseGameplayTag(CharacterTag);
		}
	}
}
