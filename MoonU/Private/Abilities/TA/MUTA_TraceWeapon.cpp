// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_TraceWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MUDefines.h"
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
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	const IGenericTeamAgentInterface* SourceActorTeam = CastChecked<IGenericTeamAgentInterface>(SourceActor);

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
	
	ProcessHitResult(HitResults);
}
