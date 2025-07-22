// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_Trace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MUDefines.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Interface/MUPlayer.h"


class IGenericTeamAgentInterface;
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
	//Need To Define When Inherited
}

void AMUTA_Trace::InitializeData(int32 Combo, TSubclassOf<UGameplayEffect> DamageEffect)
{
	CurrentCombo = Combo;
	DamageEffectClass = DamageEffect;
}

void AMUTA_Trace::ProcessHitResult(const TArray<FHitResult>& HitResults)
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	
	const IGenericTeamAgentInterface* SourceActorTeam = CastChecked<IGenericTeamAgentInterface>(SourceActor);

	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	
	for (const auto& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (SourceActorTeam->GetTeamAttitudeTowards(*HitActor) != ETeamAttitude::Hostile)
			{
				continue;
			}
			
			if (!QueryActors.Contains(HitActor))
			{
				QueryActors.Add(HitActor);

				// 쿼리 액터에 없는 경우 (판단이 아직 안된 객체의 경우 최초 감지 시, HitResult와 함께 넘겨준다.)
				
				FGameplayEventData GameplayEventData;
				GameplayEventData.Instigator = OwningAbility->GetAvatarActorFromActorInfo();
				GameplayEventData.EventMagnitude = CurrentCombo;
				FGameplayAbilityTargetData_SingleTargetHit* SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
				
				GameplayEventData.TargetData.Add(SingleTargetHit);

				//Hit가 된 캐릭터에게 즉각적으로 데미지를 가하는 로직.
				UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
				if ( IsValid(SourceASC) == true ) 
				{
					FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
					FGameplayEffectSpecHandle EffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, CurrentCombo, EffectContext);

					if (EffectSpecHandle.IsValid())
					{
						SourceASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
					}
				}
				
				//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, MU_EVENT_ONHIT, GameplayEventData);
			}
		}
	} 
}
