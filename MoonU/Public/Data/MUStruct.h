// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEnum.h"
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