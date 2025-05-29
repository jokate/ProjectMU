// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUSkillIndicator.h"
#include "Data/MUEnum.h"
#include "MUIndicatorManageSubsystem.generated.h"

/**
 * 
 */
class AMUSkillIndicator;

UCLASS()
class MOONU_API UMUIndicatorManageSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public :
	void RegisterIndicator( FName IndicatorID, AMUSkillIndicator* Indicator );

	AMUSkillIndicator* GetIndicatorByType( FName IndicatorID );

	bool HasIndicator( FName IndicatorID ) const { return IndicatorManagement.Contains(IndicatorID); }

public :
	UPROPERTY()
	TMap<FName, AMUSkillIndicator*> IndicatorManagement;
};
