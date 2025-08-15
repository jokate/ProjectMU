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


USTRUCT( BlueprintType )
struct FMUEnforcementSelection
{
	GENERATED_BODY()

public :
	UPROPERTY( BlueprintReadOnly )
	int32 CharacterID;

	UPROPERTY( BlueprintReadOnly )
	int32 EnforcementID;

	// 구조상 맞지 않지만 포괄적인 부분을 가져가기 위함.
	UPROPERTY( BlueprintReadOnly )
	FName EnforcementName;

	UPROPERTY( BlueprintReadOnly )
	ESkillSlotType EnforcementSlot;
};

// Purpose : 강화 요소 중 다시 돌렸을 시 코스트 및 레벨을 가져올 수 있도록 설계가 필요함.
// 데이터 구성 관련한 부분이 어떠헤 되어야 할 지 고민임.
USTRUCT( BLueprintType )
struct FMUEnforcementRerollCost
{
	GENERATED_BODY()

public :
	
	//UPROPERTY( BlueprintReadOnly )
};