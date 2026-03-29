// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MUGroggyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGroggyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
	UMUGroggyAttributeSet();
	
public :
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentGroggy;

	UPROPERTY(BlueprintReadOnly, Category = "Stamina", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxGroggy;
};
