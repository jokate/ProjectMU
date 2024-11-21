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

void UMUDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG( LogTemp, Log, TEXT("DataTableSubsystem Initialized"));
}
