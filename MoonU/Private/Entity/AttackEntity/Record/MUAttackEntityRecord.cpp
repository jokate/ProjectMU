// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/Record/MUAttackEntityRecord.h"

#include "Components/MUCharacterRecordComponent.h"


// Sets default values
AMUAttackEntityRecord::AMUAttackEntityRecord()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	CharacterRecordComponent = CreateDefaultSubobject<UMUCharacterRecordComponent>("CharacterRecordComponent");
	
	CharacterRecordComponent->PlayPolicy.bForce = true;
}

void AMUAttackEntityRecord::AllocateRecord(const TArray<FMUCharacterRecordData>& DataArray) const
{
	CharacterRecordComponent->RecordDatas = DataArray;
}

