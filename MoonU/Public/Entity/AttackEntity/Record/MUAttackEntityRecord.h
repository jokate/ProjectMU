// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "MUAttackEntityRecord.generated.h"

struct FMUCharacterRecordData;
class UMUCharacterRecordComponent;

UCLASS()
class MOONU_API AMUAttackEntityRecord : public AMUAttackEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAttackEntityRecord();
	void AllocateRecord(const TArray<FMUCharacterRecordData>& DataArray) const;
protected:
	
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMUCharacterRecordComponent> CharacterRecordComponent;
};
