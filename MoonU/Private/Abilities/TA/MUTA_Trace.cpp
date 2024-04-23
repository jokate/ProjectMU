// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_Trace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Abilities/GameplayAbility.h"


// Sets default values
AMUTA_Trace::AMUTA_Trace()
{
}

void AMUTA_Trace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(MU_EVENT_TRACEEND);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AMUTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (!ASC)
	{
		return;	
	}

	ASC->GenericGameplayEventCallbacks.FindOrAdd(MU_EVENT_TRACEEND).AddUObject(this, &ThisClass::OnAnimNotifyStateEnd);
}

FGameplayAbilityTargetDataHandle AMUTA_Trace::MakeTargetData()
{
	return FGameplayAbilityTargetDataHandle();
}

void AMUTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		
		if (TargetDataReadyDelegate.IsBound())
		{
			TargetDataReadyDelegate.Broadcast(DataHandle);
		}
	}
}

void AMUTA_Trace::OnAnimNotifyStateEnd(const FGameplayEventData* EventData)
{
	ConfirmTargeting();
}

void AMUTA_Trace::TraceStart()
{
}

void AMUTA_Trace::SetComboData(int32 Combo)
{
	CurrentCombo = Combo;
}
