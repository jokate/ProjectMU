// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StageManagingComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageStarted, FName, StageName );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageCleared, FName, StageName );

UCLASS()
class MOONU_API UStageManagingComponent : public UObject
{
	GENERATED_BODY()
public :

	virtual void StartStage( FName StageName );

	virtual void EndStage();
	
	virtual void RegisterUnit( FName UnitName );

	virtual void UnregisterUnit( FName UnitName );
	
public :

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnStageStarted OnStageStarted;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnStageCleared OnStageCleared;
	
	UPROPERTY( VisibleAnywhere )
	TMap<FName, int32> StageCount;

	UPROPERTY( VisibleAnywhere )
	FName CurrentStageName = NAME_None;
};
