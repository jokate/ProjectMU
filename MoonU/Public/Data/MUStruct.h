// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AI/AIEnum.h"
#include "DataTable/MUData.h"
#include "UObject/Object.h"
#include "MUStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDataDrivenBox
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform BoxTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxExtent;
};

USTRUCT(BlueprintType)
struct FAIBlackboardKey
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBlackboardKeyData> BlackboardKeyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BlackboardKeyName;
};

USTRUCT( BlueprintType )
struct FGameplayEventData_Skill : public FGameplayEventData
{
	GENERATED_BODY()

public : 
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Casting Range")
	float CastingRange = 0;
};

USTRUCT( BlueprintType )
struct FDrawingCoordinate
{
	GENERATED_BODY()

	public :
		UPROPERTY( BlueprintReadOnly )
	TArray<FVector2D> Coordinates;
};

USTRUCT( BlueprintType )
struct FMUEnforcementAllocate
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int32> AttributeMap;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<ESkillSlotType, int32> AllocatedSkillID;
};
