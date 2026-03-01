// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/MUDataTableSubsystem.h"

#include "DataRegistry.h"
#include "DataRegistrySubsystem.h"
#include "Data/MUDataPrimaryAsset.h"
#include "Framework/MUGameInstance.h"

UMUDataPrimaryAsset* UMUDataTableSubsystem::GetDataPrimaryAsset()
{
	UWorld* World = GetWorld();

	if ( IsValid(World) == false )
	{
		return nullptr;
	}

	UMUGameInstance* GI = World->GetGameInstance<UMUGameInstance>();

	if ( IsValid(GI) == false )
	{
		return nullptr;
	}

	UMUDataPrimaryAsset* DA = GI->DatasetGlobal.LoadSynchronous();

	if ( IsValid(DA) == false )
	{
		return nullptr;
	}

	return DA;
}

bool UMUDataTableSubsystem::GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FMUInputMapper>(DA->InputMapperDataRegistryType, FName(FString::FromInt(InCharacterID)), InputMapperData);
}

bool UMUDataTableSubsystem::GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FMUCharacterInfo>(DA->CharacterDataRegistryType, FName(FString::FromInt(InCharacterID)), OutCharacterInfo);
}

bool UMUDataTableSubsystem::GetEnforcementData(int32 InEnforcementID, FMUEnforcementData& OutEnforcementData)
{
	if ( IsValid(EnforcementDataTable) == false)
	{
		UDataTable* EnforcementDataTableLoaded = EnforcementDataTablePath.LoadSynchronous();
		if ( IsValid(EnforcementDataTableLoaded) == false)
		{
			UE_LOG( LogTemp, Log, TEXT("Enforcement DataTable Is Not Valid") );
			return false;
		}

		EnforcementDataTable = EnforcementDataTableLoaded;
	}

	bool bEnforcementData = false;
	EnforcementDataTable->ForeachRow<FMUEnforcementData>
	(TEXT(""),[&] (const FName& Key, const FMUEnforcementData& Value)
	{
		if ( Value.EnforcementID == InEnforcementID )
		{
			UE_LOG(LogTemp, Log, TEXT("Enforcement Founded"));
			OutEnforcementData = Value;
			bEnforcementData = true;
		}	
	});

	return bEnforcementData;
}

bool UMUDataTableSubsystem::GetEnforcementDropData(int32 Level, FMUEnforcementDropSelect& OutEnforcementDropSelect)
{
	if ( IsValid(EnforcementDropTable) == false)
    {
    	UDataTable* EnforcementDataTableLoaded = EnforcementDropTablePath.LoadSynchronous();
    	if ( IsValid(EnforcementDataTableLoaded) == false)
    	{
    		UE_LOG( LogTemp, Log, TEXT("Enforcement Drop DataTable Is Not Valid") );
    		return false;
    	}

    	EnforcementDropTable = EnforcementDataTableLoaded;
    }

    EnforcementDropTable->ForeachRow<FMUEnforcementDropSelect>
    (TEXT(""),[&] (const FName& Key, const FMUEnforcementDropSelect& Value)
    {
    	if ( Value.Level == Level )
    	{
    		OutEnforcementDropSelect = Value;
    	}	
    });

    return true;
}

bool UMUDataTableSubsystem::GetEnforcementDropDataByRegistry(FName DataRegistryName, int32 Level,
	FMUEnforcementDropSelect& OutEnforcementDropSelect )
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FMUEnforcementDropSelect>(DataRegistryName, FName(FString::FromInt(Level)), OutEnforcementDropSelect);
}

bool UMUDataTableSubsystem::GetSkillData(FName SkillName, FMUSkillData& OutSkillData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return  GetRegistryData<FMUSkillData>(DA->SkillDataRegistryType, SkillName, OutSkillData);
}

bool UMUDataTableSubsystem::GetStageInfoData(FName StageInfoName, FMUStageInfo& OutStageInfo)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return  GetRegistryData<FMUStageInfo>(DA->StageInfoDataRegistryType, StageInfoName, OutStageInfo);
}

bool UMUDataTableSubsystem::GetStageData(FName StageName, FMUStageData& OutStageData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return  GetRegistryData<FMUStageData>(DA->StageDataRegistryType, StageName, OutStageData);
}

bool UMUDataTableSubsystem::GetMonsterSpawnData(FName SpawnerName, FMUMonsterSpawnList& OutSpawnerData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FMUMonsterSpawnList>(DA->MonsterSpawnDataRegistryType, SpawnerName, OutSpawnerData);
}

bool UMUDataTableSubsystem::GetSkillTreeWidgetInfo(int32 CharacterID, FEnforcementWidgetData& EnforcementWidgetData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FEnforcementWidgetData>(DA->SkillTreeWidgetDatRegistryType, FName(FString::FromInt(CharacterID)), EnforcementWidgetData);
}

bool UMUDataTableSubsystem::GetTopMenuWidgetData(FName Name, FTopMenuData& OutMenuData)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}
	
	return GetRegistryData<FTopMenuData>(DA->TopMenuWidgetDataRegistryType, Name, OutMenuData);
}

bool UMUDataTableSubsystem::GetDamageInfoData(FName Name, FMUDamageInfo& OutDamageInfo)
{
	UMUDataPrimaryAsset* DA = GetDataPrimaryAsset();
	
	if ( IsValid(DA) == false )
	{
		return false; 
	}

	return GetRegistryData<FMUDamageInfo>(DA->DamageDataRegistryType, Name, OutDamageInfo);
}

bool UMUDataTableSubsystem::GetAllCombatComboData(TArray<FMUInputCommandList>& OutCombatComboData)
{
	if ( IsValid(CombatComboDataTable) == false)
	{
		UDataTable* CombatComboDataTableLoaded = CombatComboDataTablePath.LoadSynchronous();
		if ( IsValid(CombatComboDataTableLoaded) == false)
		{
			UE_LOG( LogTemp, Log, TEXT("Combat Combo DataTable Is Not Valid") );
			return false;
		}

		CombatComboDataTable = CombatComboDataTableLoaded;
	}

	CombatComboDataTable->ForeachRow<FMUInputCommandList>
	(TEXT(""),[&] (const FName& Key, const FMUInputCommandList& Value)
	{
		OutCombatComboData.Add(Value);
	});

	return true;
}

void UMUDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG( LogTemp, Log, TEXT("DataTableSubsystem Initialized"));
}

template <typename T>
bool UMUDataTableSubsystem::GetRegistryData(FName RegistryName, FName RowName, T& OutData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = RegistryName;
	RegistryId.ItemName = RowName;

	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}
	
	const T* Type = DataRegistrySubsystem->GetCachedItem<T>(RegistryId);
	
	if ( Type == nullptr )
	{
		return false;
	}

	OutData = *Type;
	return true;
}

template bool UMUDataTableSubsystem::GetRegistryData<FMUAttackEntityData>(FName, FName, FMUAttackEntityData&);
template bool UMUDataTableSubsystem::GetRegistryData<FMUProjectileInfo>(FName, FName, FMUProjectileInfo&);
