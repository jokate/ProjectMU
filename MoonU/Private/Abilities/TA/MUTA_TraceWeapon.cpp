// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_TraceWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Data/MUEnum.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AMUTA_TraceWeapon::AMUTA_TraceWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponSocketName = TEXT("Weapon_R_Trail_A");
}

void AMUTA_TraceWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TraceStart();
}

void AMUTA_TraceWeapon::TraceStart()
{
	Super::TraceStart();

	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	const auto* MeshComp = Character->GetMesh();

	if (!MeshComp)
	{
		return;
	}

	const FVector& WeaponSocketLocation = MeshComp->GetSocketLocation(WeaponSocketName);
	const FVector End = WeaponSocketLocation + FVector::UpVector;
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	ActorsToIgnore.Add(Character);
	UKismetSystemLibrary::SphereTraceMultiByProfile(this, WeaponSocketLocation,
		End, 50.0f, TEXT("Weapon"), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true,
		FLinearColor::Red, FLinearColor::Green, 1.0f);

	for (const auto& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (!QueryActors.Contains(HitActor))
			{
				QueryActors.Add(HitActor);

				// 쿼리 액터에 없는 경우 (판단이 아직 안된 객체의 경우 최초 감지 시, HitResult와 함께 넘겨준다.
				
				FGameplayEventData GameplayEventData;

				GameplayEventData.EventMagnitude = CurrentCombo;
				FGameplayAbilityTargetData_SingleTargetHit* SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
				
				GameplayEventData.TargetData.Add(SingleTargetHit);

				UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
				if (ASC)
				{
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, CurrentCombo, EffectContext);

					if (EffectSpecHandle.IsValid())
					{
						ASC->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
					}
				}
				
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, MU_EVENT_ONHIT, GameplayEventData);
			}
		}
	} 
}
