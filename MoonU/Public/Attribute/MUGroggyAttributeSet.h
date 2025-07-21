// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MUGroggyAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

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
