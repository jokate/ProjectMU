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
	UFUNCTION(BlueprintCallable)
	virtual bool GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData);

	UFUNCTION(BlueprintCallable)
	virtual bool GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo);

	UFUNCTION(BlueprintCallable)
	virtual bool GetEnforcementData(int32 InEnforcementID, FMUEnforcementData& OutEnforcementData);

	UFUNCTION(BlueprintCallable)
	virtual bool GetEnforcementDropData(int32 Level, FMUEnforcementDropSelect& OutEnforcementDropSelect);

	UFUNCTION( BlueprintCallable )
	virtual bool GetSkillData( FName SkillName, FMUSkillData& OutSkillData );	
protected :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
protected :
	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> CharacterInfoDataTablePath;
	
	UPROPERTY()
	TObjectPtr<UDataTable> CharacterInfoDataTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> InputMapperDataTablePath;
	
	UPROPERTY()
	TObjectPtr<UDataTable> InputMapperDataTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> EnforcementDataTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> EnforcementDataTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> EnforcementDropTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> EnforcementDropTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> SkillDataTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> SkillDataTable;
};
