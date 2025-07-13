// Fill out your copyright notice in the Description page of Project Settings.


#include "MUAIAbilitySystemComponent.h"

#include "Interface/RetriggerAbility.h"


// Sets default values for this component's properties
UMUAIAbilitySystemComponent::UMUAIAbilitySystemComponent()
{
}

int32 UMUAIAbilitySystemComponent::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	int32 TriggerCount = 0;
	FGameplayTag CurrentTag = EventTag;
	
	while (CurrentTag.IsValid())
	{
		if (GameplayEventTriggeredAbilities.Contains(CurrentTag))
		{
			TArray<FGameplayAbilitySpecHandle> TriggeredAbilityHandles = GameplayEventTriggeredAbilities[CurrentTag];

			for (FGameplayAbilitySpecHandle& AbilityHandle : TriggeredAbilityHandles)
			{
				if ( RetriggerAbility(AbilityHandle ) == true )
				{
					TriggerCount++;
				}
			}
		}

		CurrentTag = CurrentTag.RequestDirectParent();
	}
	
	TriggerCount += Super::HandleGameplayEvent(EventTag, Payload);

	return TriggerCount;
}

bool UMUAIAbilitySystemComponent::RetriggerAbility(FGameplayAbilitySpecHandle& AbilitySpec)
{
	FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(AbilitySpec);

	if ( Spec == nullptr)
	{
		return false;	
	}

	UGameplayAbility* InstancedAbility = Spec->GetPrimaryInstance();
	UGameplayAbility* Ability = InstancedAbility ? InstancedAbility : Spec->Ability;

	if ( IsValid(Ability) == false )
	{
		return false;
	}

	IRetriggerAbility* RetriggerAbility = Cast<IRetriggerAbility>(Ability);

	if ( RetriggerAbility == nullptr )
	{
		return false;
	}

	RetriggerAbility->RetriggerAbility();

	return true;
}
