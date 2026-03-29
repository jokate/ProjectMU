// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Data/TimeWinder/MUTimeWindData.h"
#include "MUCharacterRecordAttribute.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUCharacterRecordAttribute : public UAttributeSet
{
	GENERATED_BODY()


public :
	
	UPROPERTY()
	FGameplayAttributeData MaxRecordCount = 0;

	UPROPERTY()
	FGameplayAttributeData CurrentRecordCount = 0;
};
