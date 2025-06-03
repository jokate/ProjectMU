// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_TimeStop.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Attribute/MUTimewinderAttribute.h"
#include "Interface/TimeStopper.h"

UMUGA_TimeStop::UMUGA_TimeStop()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_TimeStop::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	
	ITimeStopper* TimeStopper = Cast<ITimeStopper>(GetWorld()->GetAuthGameMode());

	if (TimeStopper)
	{
		TimeStopper->TimeStopDeactivate();
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_TimeStop::OnTimeFinished()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_TimeStop::ActivateSkill()
{
	ITimeStopper* TimeStopper = Cast<ITimeStopper>(GetWorld()->GetAuthGameMode());

	if (TimeStopper)
	{
		TimeStopper->TimeStopActivate();
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	
	if (ASC)
	{
		const UMUTimewinderAttribute* CharacterAttribute = ASC->GetSet<UMUTimewinderAttribute>();

		if (CharacterAttribute)
		{
			GetWorld()->GetTimerManager().SetTimer(TimeStopHandle, this, &UMUGA_TimeStop::OnTimeFinished, CharacterAttribute->GetTimeStopDuration(), false);
		}

		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->ExecuteGameplayCue(GameplayCueTag);
		}
	}
}
