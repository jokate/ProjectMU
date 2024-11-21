// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUFunctionLibrary.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Singleton/MUDataTableSubsystem.h"

ACharacter* UMUFunctionLibrary::GetLocalPlayerCharacter(UObject* WorldObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldObject, 0);
}

FGameplayTag UMUFunctionLibrary::GetInteractableGameplayTag(UObject* InteractableTarget)
{
	auto* Target = Cast<IInteractableTarget>(InteractableTarget);

	if (Target == nullptr)
	{
		return FGameplayTag();
	}
	
	return Target->GetEntityTag();
}

UGameInstance* UMUFunctionLibrary::GetGameInstance(UObject* Object)
{
	if ( IsValid(Object) == false)
	{
		return nullptr;
	}

	UWorld* World = Object->GetWorld();

	if ( IsValid(World) == false)
	{
		return nullptr;	
	}
	
	return World->GetGameInstance();
}

bool UMUFunctionLibrary::GetInputMapperData(UObject* Object, int32 InCharacterID, FMUInputMapper& InputMapperData)
{
	UGameInstance* GameInstance = GetGameInstance(Object);

	if ( IsValid(GameInstance) == false)
	{
		return false;
	}

	UMUDataTableSubsystem* DataTableSubsystem = GameInstance->GetSubsystem<UMUDataTableSubsystem>();

	if ( IsValid(DataTableSubsystem) == false )
	{
		return false;
	}

	return DataTableSubsystem->GetInputMapperData(InCharacterID, InputMapperData);
}

bool UMUFunctionLibrary::GetCharacterInfoData(UObject* Object, int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo)
{
	UGameInstance* GameInstance = GetGameInstance(Object);

    if ( IsValid(GameInstance) == false)
    {
    	return false;
    }

    UMUDataTableSubsystem* DataTableSubsystem = GameInstance->GetSubsystem<UMUDataTableSubsystem>();

    if ( IsValid(DataTableSubsystem) == false )
    {
    	return false;
    }

    return DataTableSubsystem->GetCharacterInfoData(InCharacterID, OutCharacterInfo);
}

