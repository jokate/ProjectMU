// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "MUTimeWindData.generated.h"

USTRUCT(BlueprintType)
struct FTimeWindMontageRecordData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UAnimMontage> Montage;

	UPROPERTY(VisibleAnywhere)
	float MontagePosition;
};

USTRUCT(BlueprintType)
struct FAttributeChangedRecord
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float OldValue;
};

USTRUCT(BlueprintType)
struct FTimeWindRecordData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimeWindMontageRecordData MontageRecordData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector RewindVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FAttributeChangedRecord> AttributeChangedRecords;
};
