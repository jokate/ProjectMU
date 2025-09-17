// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataTable/MUData.h"
#include "Data/DataTable/MUWidgetData.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MUDataTableSubsystem.generated.h"


class UMUDataPrimaryAsset;
/**
 * 
 */
UCLASS(Config = Game)
class MOONU_API UMUDataTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	virtual UMUDataPrimaryAsset* GetDataPrimaryAsset();
	UFUNCTION( BlueprintCallable )
	virtual bool GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData);

	UFUNCTION( BlueprintCallable )
	virtual bool GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo);

	UFUNCTION( BlueprintCallable )
	virtual bool GetEnforcementData(int32 InEnforcementID, FMUEnforcementData& OutEnforcementData);

	UFUNCTION( BlueprintCallable )
	virtual bool GetEnforcementDropData(int32 Level, FMUEnforcementDropSelect& OutEnforcementDropSelect);

	UFUNCTION( BlueprintPure )
	virtual bool GetEnforcementDropDataByRegistry( FName DataRegistryName, int32 Level, FMUEnforcementDropSelect& OutEnforcementDropSelect); 

	UFUNCTION( BlueprintCallable )
	virtual bool GetSkillData( FName SkillName, FMUSkillData& OutSkillData );

	UFUNCTION( BlueprintCallable )
	virtual bool GetStageInfoData( FName StageInfoName, FMUStageInfo& OutStageInfo );

	UFUNCTION( BlueprintCallable )
	virtual bool GetStageData( FName StageName, FMUStageData& OutStageData );

	UFUNCTION( BlueprintCallable )
	virtual bool GetMonsterSpawnData( FName SpawnerName, FMUMonsterSpawnList& OutSpawnerData );

	UFUNCTION( BlueprintPure )
	virtual bool GetSkillTreeWidgetInfo( int32 CharacterID, FEnforcementWidgetData& EnforcementWidgetData );

	UFUNCTION( BlueprintPure )
	virtual bool GetTopMenuWidgetData( FName Name, FTopMenuData& OutMenuData );

	template<typename T>
	bool GetRegistryData( FName RegistryName, FName RowName, T& OutData );

	UFUNCTION( BlueprintPure )
	virtual bool GetAllCombatComboData( TArray<FMUInputCommandList>& OutCombatComboData );
	
protected :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
protected :
	
	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> EnforcementDataTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> EnforcementDataTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> EnforcementDropTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> EnforcementDropTable;

	UPROPERTY(Config)
	TSoftObjectPtr<UDataTable> CombatComboDataTablePath;

	UPROPERTY()
	TObjectPtr<UDataTable> CombatComboDataTable;
};
