// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUSkillIndicator.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Data/MUEnum.h"
#include "MUIndicatorManageSubsystem.generated.h"

/**
 * 
 */

class AMUCameraActor;
// 풀링 시스템 구축을 위한 작업.
class AMUSkillIndicator;

UCLASS()
class MOONU_API UMUIndicatorManageSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public :

	virtual void ActivateSkillIndicator( FName IndicatorID );
	virtual void DeactivateSkillIndicator( FName IndicatorID );
	
	void UnRegisterIndicator( FName IndicatorID );

	AMUSkillIndicator* GetIndicatorByID( FName IndicatorID );

	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;

	virtual void SetupCamera( FName IndicatorID );
	virtual void DeactivateCamera();

	virtual FVector GetIndicatorTargetLocation( FName IndicatorID );
	virtual FRotator GetIndicatorTargetRotation( FName IndicatorID );

	FORCEINLINE bool IsSkillActive() const { return bIsSkillMode; }

protected :
	
	bool HasIndicator( FName IndicatorID ) const { return IndicatorManagement.Contains(IndicatorID); }
	
	bool RegisterIndicator( FName IndicatorID );

	UFUNCTION()
	virtual void ReserveCamMove();

	
public :
	UPROPERTY()
	TMap<FName, AMUSkillIndicator*> IndicatorManagement;

	UPROPERTY()
	TObjectPtr<AMUCameraActor> IndicatorCameraActor;

	UPROPERTY()
	APawn* LocalPlayerActor;

	UPROPERTY()
	bool bIsSkillMode = false;
	
	UPROPERTY()
	APlayerController* LocalPlayerController;

	FTimerHandle ChangeCamTimerHandle;
};