// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUGameSettings.h"
#include "Engine/GameInstance.h"
#include "MUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UMUGameInstance();

public :
	UPROPERTY( EditDefaultsOnly )
	TSoftObjectPtr<class UMUPrimaryDataAsset> EnforcementGlobal;

	UPROPERTY( EditDefaultsOnly )
	TSoftObjectPtr<class UMUDataPrimaryAsset> DatasetGlobal;
};
