// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_TraceWeapon.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AMUTA_TraceWeapon::AMUTA_TraceWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponSocketName = TEXT("Weapon");
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
		End, 50.0f, TEXT("WEAPON"), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true,
		FLinearColor::Red, FLinearColor::Green, 1.0f);

	for (const auto& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (!QueryActors.Contains(HitActor))
			{
				QueryActors.Add(HitActor);
			}
		}
	} 
}

FGameplayAbilityTargetDataHandle AMUTA_TraceWeapon::MakeTargetData()
{
	FGameplayAbilityTargetData_ActorArray* ActorsData = new FGameplayAbilityTargetData_ActorArray();
	ActorsData->SetActors(QueryActors);

	return FGameplayAbilityTargetDataHandle(ActorsData);
}
