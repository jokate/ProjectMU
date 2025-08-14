// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/MUDataTableSubsystem.h"

#include "DataRegistry.h"
#include "DataRegistrySubsystem.h"

bool UMUDataTableSubsystem::GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = InputMapperDataRegistryType;
	RegistryId.ItemName = FName(FString::FromInt(InCharacterID	));
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUInputMapper* InputMapper = DataRegistrySubsystem->GetCachedItem<FMUInputMapper>(RegistryId);
	
	if ( InputMapper == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	InputMapperData = *InputMapper;
	return true;
}

bool UMUDataTableSubsystem::GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = CharacterDataRegistryType;
	RegistryId.ItemName = FName(FString::FromInt(InCharacterID));
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUCharacterInfo* CharacterInfo = DataRegistrySubsystem->GetCachedItem<FMUCharacterInfo>(RegistryId);
	
	if ( CharacterInfo == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutCharacterInfo = *CharacterInfo;
	return true;
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
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = DataRegistryName;
	RegistryId.ItemName = FName(FString::Printf(TEXT("%d"), Level));;
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUEnforcementDropSelect* EnforcementDrop = DataRegistrySubsystem->GetCachedItem<FMUEnforcementDropSelect>(RegistryId);
	
	if ( EnforcementDrop == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutEnforcementDropSelect = *EnforcementDrop;
	return true;
}

bool UMUDataTableSubsystem::GetSkillData(FName SkillName, FMUSkillData& OutSkillData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = SkillDataRegistryType;
	RegistryId.ItemName = SkillName;
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUSkillData* SkillData = DataRegistrySubsystem->GetCachedItem<FMUSkillData>(RegistryId);
	
	if ( SkillData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutSkillData = *SkillData;
	return true;
}

bool UMUDataTableSubsystem::GetStageInfoData(FName StageInfoName, FMUStageInfo& OutStageInfo)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = StageInfoDataRegistryType;
	RegistryId.ItemName = StageInfoName;
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUStageInfo* StageInfoData = DataRegistrySubsystem->GetCachedItem<FMUStageInfo>(RegistryId);
	
	if ( StageInfoData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutStageInfo = *StageInfoData;
	return true;
}

bool UMUDataTableSubsystem::GetStageData(FName StageName, FMUStageData& OutStageData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = StageDataRegistryType;
	RegistryId.ItemName = StageName;
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUStageData* StageData = DataRegistrySubsystem->GetCachedItem<FMUStageData>(RegistryId);
	
	if ( StageData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutStageData = *StageData;
	
	return true;
}

bool UMUDataTableSubsystem::GetMonsterSpawnData(FName SpawnerName, FMUMonsterSpawnList& OutSpawnerData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = MonsterSpawnDataRegistryType;
	RegistryId.ItemName = SpawnerName;
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FMUMonsterSpawnList* MonsterSpawnerData = DataRegistrySubsystem->GetCachedItem<FMUMonsterSpawnList>(RegistryId);
	
	if ( MonsterSpawnerData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutSpawnerData = *MonsterSpawnerData;
	return true;
}

bool UMUDataTableSubsystem::GetSkillTreeWidgetInfo(int32 CharacterID, FEnforcementWidgetData& EnforcementWidgetData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = SkillTreeWidgetDatRegistryType;
	RegistryId.ItemName = FName( FString::FromInt(CharacterID));
	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FEnforcementWidgetData* SkillTreeData = DataRegistrySubsystem->GetCachedItem<FEnforcementWidgetData>(RegistryId);
	
	if ( SkillTreeData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	EnforcementWidgetData = *SkillTreeData;
	return true;
}

bool UMUDataTableSubsystem::GetTopMenuWidgetData(FName Name, FTopMenuData& OutMenuData)
{
	FDataRegistryId RegistryId;
	RegistryId.RegistryType = TopMenuWidgetDataRegistryType;
	RegistryId.ItemName = Name;

	
	UDataRegistrySubsystem* DataRegistrySubsystem = UDataRegistrySubsystem::Get();
	
	if ( IsValid(DataRegistrySubsystem) == false )
	{
		return false;
	}

	const FTopMenuData* TopMenuData = DataRegistrySubsystem->GetCachedItem<FTopMenuData>(RegistryId);
	
	if ( TopMenuData == nullptr )
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Preloaded Complete"));
	OutMenuData = *TopMenuData;
	return true;
}

void UMUDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG( LogTemp, Log, TEXT("DataTableSubsystem Initialized"));
}
