// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/MUAttackEntity.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/MUCharacterBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMUAttackEntity::AMUAttackEntity()
{
}

void AMUAttackEntity::RegisterOwner(AActor* InSpawnedOwwner)
{
	SpawnedOwner = InSpawnedOwwner;
}

UAbilitySystemComponent* AMUAttackEntity::GetAbilitySystemComponent() const
{
	AActor* TempSpawnedOwner = SpawnedOwner.Get();

	if ( IsValid(TempSpawnedOwner) == false )
	{
		return nullptr;
	}

	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TempSpawnedOwner);
}




