// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/MUProjectileEntity.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Data/MUDataPrimaryAsset.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Library/MUFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AMUProjectileEntity::AMUProjectileEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("BulletParticleSystem");
}

TArray<AActor*> AMUProjectileEntity::GetAttackableActorList()
{
	TArray<FHitResult> OutHit;
	FVector StartLoc = GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(SpawnedOwner);

	// 사실 Sphere로 해도 괼거 같기는 하다..
	UKismetSystemLibrary::SphereTraceMultiByProfile(this, StartLoc, StartLoc + FVector::OneVector,
		ProjectileInfoData.CapsuleRadius, TEXT("Weapon"), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true );

	TArray<AActor*> OutHitActors;
	for ( const FHitResult& Result : OutHit)
	{
		OutHitActors.Emplace(Result.GetActor());
	}
	
	return OutHitActors;
}

void AMUProjectileEntity::OnReacted(AActor* ReactedActor)
{
	Super::OnReacted(ReactedActor);

	// 적용 목적으로 하는 이펙트셋 적용.
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SpawnedOwner);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ReactedActor);
	if ( IsValid(SourceASC) == true ) 
	{
		FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = SourceASC->MakeOutgoingSpec(ProjectileInfoData.HitEffect, 0, EffectContext);

		if (EffectSpecHandle.IsValid())
		{
			SourceASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
		}
	}

	ProjectileInfoData.HitCount--;
}

bool AMUProjectileEntity::CheckReact(AActor* ReactTarget) const
{
	if ( ProjectileInfoData.HitCount <= 0 )
	{
		return false; 
	}
	
	return Super::CheckReact(ReactTarget);
}

void AMUProjectileEntity::SetupProjectileInfo()
{
	UMUDataPrimaryAsset* DataPrimaryAsset = UMUFunctionLibrary::GetDataPrimaryAsset( this );

	if ( IsValid( DataPrimaryAsset ) == true )
	{
		UMUFunctionLibrary::GetRegistryData<FMUProjectileInfo>(this, DataPrimaryAsset->ProjectileRegistryType,ProjectileInfo,ProjectileInfoData);
	}

	if ( IsValid(ProjectileMovementComponent) )
	{
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(0, 0, 1) * ProjectileInfoData.ProjectileSpeed);
	}
}

void AMUProjectileEntity::BeginPlay()
{
	Super::BeginPlay();

	SetupProjectileInfo();
}
