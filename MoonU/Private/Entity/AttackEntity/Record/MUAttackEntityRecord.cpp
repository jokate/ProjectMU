// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/Record/MUAttackEntityRecord.h"

#include "Components/MUCharacterRecordComponent.h"


// Sets default values
AMUAttackEntityRecord::AMUAttackEntityRecord()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	CharacterRecordComponent = CreateDefaultSubobject<UMUCharacterRecordComponent>("CharacterRecordComponent");

	SetRootComponent(Root);
	SkeletalMesh->SetupAttachment(Root);
	
	CharacterRecordComponent->PlayPolicy.bForce = true;
}

void AMUAttackEntityRecord::RegisterOwner(AActor* InSpawnedOwner)
{
	Super::RegisterOwner(InSpawnedOwner);
	CharacterRecordComponent->OnInitialize();
}


void AMUAttackEntityRecord::AllocateRecord(const TArray<FMUCharacterRecordData>& DataArray) const
{
	CharacterRecordComponent->RecordDatas = DataArray;
}

