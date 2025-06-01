// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUSkillIndicator.h"
#include "Data/MUEnum.h"
#include "MUIndicatorManageSubsystem.generated.h"

/**
 * 
 */

// 풀링 시스템 구축을 위한 작업.
class AMUSkillIndicator;

UCLASS()
class MOONU_API UMUIndicatorManageSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public :

	void UnRegisterIndicator( FName IndicatorID );

	AMUSkillIndicator* GetIndicatorByID( FName IndicatorID );

	bool HasIndicator( FName IndicatorID ) const { return IndicatorManagement.Contains(IndicatorID); }

	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;

protected :
	
	bool RegisterIndicator( FName IndicatorID );
	
public :
	UPROPERTY()
	TMap<FName, AMUSkillIndicator*> IndicatorManagement;

	UPROPERTY()
	APawn* LocalPlayerActor;

	UPROPERTY()
	APlayerController* LocalPlayerController;
};
