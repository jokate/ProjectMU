// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_SetValueForBlackboard.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMUGA_SetValueForBlackboard::UMUGA_SetValueForBlackboard()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bRetriggerInstancedAbility = true;
}

void UMUGA_SetValueForBlackboard::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	TryChangeBlackboardValue();
}

void UMUGA_SetValueForBlackboard::TryChangeBlackboardValue()
{
	APawn* TargetPawn = Cast<APawn>(CurrentActorInfo->AvatarActor.Get());

	if (TargetPawn == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	AAIController* AIController = Cast<AAIController>(TargetPawn->GetController());

	if (AIController == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	switch (DataTypeToChange)
	{
	case BoolType :
		BBComponent->SetValueAsBool(SelectedKey, ChangeValBool);
		break;
	case FloatType:
		BBComponent->SetValueAsFloat(SelectedKey, ChangeValFloat);
		break;
	case IntType:
		BBComponent->SetValueAsInt(SelectedKey, ChangeValInt);
		break;
	case VectorType:
		BBComponent->SetValueAsVector(SelectedKey, ChangeValVector);
		break;
	case EnumType:
		{
			const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName.ToString(), true);
			if (!Enum)
			{
				break;
			}

			BBComponent->SetValueAsEnum(SelectedKey, Enum->GetValueByName(EnumValue));
		}
	default :
		UE_LOG(LogTemp, Warning, TEXT("INVALID TYPE"));
		break;
	}
	UE_LOG(LogTemp, Log, TEXT("Data Change Succeed"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}


