// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataTable/MUData.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MUDataTableSubsystem.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class MOONU_API UMUDataTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable, BlueprintCallable)
	virtual bool GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData);

	UFUNCTION(BlueprintCallable, BlueprintCallable)
	virtual bool GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo);
	
protected :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
protected :
	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> CharacterInfoDataTablePath;
	
	UPROPERTY()
	TObjectPtr<UDataTable> CharacterInfoDataTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> InputMapperDataTablePath;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> InputMapperDataTable;
};
