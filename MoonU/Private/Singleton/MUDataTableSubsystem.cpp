// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/MUDataTableSubsystem.h"

bool UMUDataTableSubsystem::GetInputMapperData(int32 InCharacterID, FMUInputMapper& InputMapperData)
{
	if ( IsValid(InputMapperDataTable) == false)
	{
		UDataTable* TempInputMapper = InputMapperDataTablePath.LoadSynchronous();
		if ( IsValid(TempInputMapper) == false)
		{
			UE_LOG( LogTemp, Log, TEXT("Input Mapper DataTable Is Not Valid"));
			return false;
		}
		InputMapperDataTable = TempInputMapper;
	}

	InputMapperDataTable->ForeachRow<FMUInputMapper>
	(TEXT(""),[&] (const FName& Key, const FMUInputMapper& Value)
	{
		if ( Value.CharacterID == InCharacterID )
		{
			InputMapperData = Value;
		}	
	});

	return true;
}

bool UMUDataTableSubsystem::GetCharacterInfoData(int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo)
{
	if ( IsValid(CharacterInfoDataTable) == false)
	{
		UDataTable* CharacterDataTableLoader = CharacterInfoDataTablePath.LoadSynchronous();
		if ( IsValid(CharacterDataTableLoader) == false)
		{
			UE_LOG( LogTemp, Log, TEXT("Character Info DataTable Is Not Valid") );
			return false;
		}

		CharacterInfoDataTable = CharacterDataTableLoader;
	}

	CharacterInfoDataTable->ForeachRow<FMUCharacterInfo>
	(TEXT(""),[&] (const FName& Key, const FMUCharacterInfo& Value)
	{
		if ( Value.CharacterID == InCharacterID )
		{
			OutCharacterInfo = Value;
		}	
	});

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

	EnforcementDataTable->ForeachRow<FMUEnforcementData>
	(TEXT(""),[&] (const FName& Key, const FMUEnforcementData& Value)
	{
		if ( Value.EnforcementID == InEnforcementID )
		{
			UE_LOG(LogTemp, Log, TEXT("Enforcement Founded"));
			OutEnforcementData = Value;
		}	
	});

	return true;
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

bool UMUDataTableSubsystem::GetSkillData(FName SkillName, FMUSkillData& OutSkillData)
{
	if ( IsValid(SkillDataTable) == false)
	{
		UDataTable* SkillDataTableLoaded = SkillDataTablePath.LoadSynchronous();
		if ( IsValid(SkillDataTableLoaded) == false)
		{
			UE_LOG( LogTemp, Log, TEXT("Skill DataTable Is Not Valid") );
			return false;
		}

		SkillDataTable = SkillDataTableLoaded;
	}

	FMUSkillData* SkillData = SkillDataTable->FindRow<FMUSkillData>( SkillName, TEXT(""));

	if ( SkillData == nullptr )
	{
		return false;
	}

	OutSkillData = *SkillData;

	return true;
}

bool UMUDataTableSubsystem::GetStageInfoData(FName StageInfoName, FMUStageInfo& OutStageInfo)
{
	if ( IsValid( StageInfoDataTable ) == false )
	{
		UDataTable* StageInfoDataTableLoaded = StageInfoDataTablePath.LoadSynchronous();

		if ( IsValid( StageInfoDataTableLoaded ) == false ) 
		{
			UE_LOG( LogTemp, Log, TEXT("StageInfo DataTable Is Not Valid") );
			return false;
		}

		StageInfoDataTable = StageInfoDataTableLoaded;
	}

	FMUStageInfo* StageInfoData = StageInfoDataTable->FindRow<FMUStageInfo>( StageInfoName, TEXT(""));

	if ( StageInfoData == nullptr )
	{
		return false;
	}

	OutStageInfo = *StageInfoData;
	
	return true;
}

bool UMUDataTableSubsystem::GetStageData(FName StageName, FMUStageData& OutStageData)
{
	if ( IsValid( StageDataTable ) == false )
	{
		UDataTable* StageDataTableLoaded = StageDataTablePath.LoadSynchronous();

		if ( IsValid( StageDataTableLoaded ) == false ) 
		{
			UE_LOG( LogTemp, Log, TEXT("Stage DataTable Is Not Valid") );
			return false;
		}

		StageInfoDataTable = StageDataTableLoaded;
	}

	FMUStageData* StageData = StageInfoDataTable->FindRow<FMUStageData>( StageName, TEXT(""));

	if ( StageData == nullptr )
	{
		return false;
	}

	OutStageData = *StageData;
	
	return true;
}

bool UMUDataTableSubsystem::GetMonsterSpawnData(FName SpawnerName, FMUMonsterSpawnData& OutSpawnerData)
{
	if ( IsValid( MonsterSpawnDataTable ) == false )
	{
		UDataTable* SpawnerDataTableLoaded = MonsterSpawnDataTablePath.LoadSynchronous();

		if ( IsValid( SpawnerDataTableLoaded ) == false ) 
		{
			UE_LOG( LogTemp, Log, TEXT("Monster DataTable Is Not Valid") );
			return false;
		}

		MonsterSpawnDataTable = SpawnerDataTableLoaded;
	}

	FMUMonsterSpawnData* SpawnerData = StageInfoDataTable->FindRow<FMUMonsterSpawnData>( SpawnerName, TEXT(""));

	if ( SpawnerData == nullptr )
	{
		return false;
	}

	OutSpawnerData = *SpawnerData;
	
	return true;
}

void UMUDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG( LogTemp, Log, TEXT("DataTableSubsystem Initialized"));
}
