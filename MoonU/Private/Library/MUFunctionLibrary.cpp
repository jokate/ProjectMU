﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUFunctionLibrary.h"

#include "Character/MUCharacterPlayer.h"
#include "Components/Input/MUEnhancedInputComponent.h"
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

bool UMUFunctionLibrary::GetEnforcementData(UObject* Object, int32 EnforcementID,
	FMUEnforcementData& OutEnforcementData)
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

	return DataTableSubsystem->GetEnforcementData(EnforcementID, OutEnforcementData);
}

bool UMUFunctionLibrary::GetEnforcementDropData(UObject* Object, int32 Level,
	FMUEnforcementDropSelect& OutEnforcementDropSelect)
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

	return DataTableSubsystem->GetEnforcementDropData(Level, OutEnforcementDropSelect);
}

bool UMUFunctionLibrary::BindInputActionByTag(AMUCharacterPlayer* CharacterPlayer, int32 CharacterID,
                                              FTagByInput& TagByInput)
{
	UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(CharacterPlayer->InputComponent);

	if ( IsValid(EnhancedInputComponent) == false)
	{
		return false;
	}
		
	FMUInputMapper InputMapper;
	if (GetInputMapperData(CharacterPlayer, CharacterID, InputMapper) == false)
	{
		return false;
	}

	TArray<FInputFunctionalType>& InputFunctionalTypes = TagByInput.InputFunctionalTypes;
			
	for ( FInputFunctionalType& InputFunctionalType : InputFunctionalTypes)
	{
		switch (InputFunctionalType.GASFunctionalType)
		{
		case Pressed:
			{
				EnhancedInputComponent->BindActionByTag(InputMapper.InputConfig,  TagByInput.InputTag,
					InputFunctionalType.TriggerEvent, CharacterPlayer, &AMUCharacterPlayer::GASInputPressed, TagByInput.InputID);
				break;
			}

		case Released:
			{
				EnhancedInputComponent->BindActionByTag(InputMapper.InputConfig, TagByInput.InputTag,
					InputFunctionalType.TriggerEvent, CharacterPlayer, &AMUCharacterPlayer::GASInputReleased, TagByInput.InputID);
				break;
			}
		default:
			{
				break;
			}
		}	
	}

	return true;
}

bool UMUFunctionLibrary::GetEnforcementDropTable(UObject* Object, int32 Level, int32 ArrCount, TSet<int32>& DropEnforcement)
{
	if (IsValid(Object) == false)
	{
		return false;
	}

	FMUEnforcementDropSelect DropSelect;
	if (GetEnforcementDropData(Object, Level, DropSelect) == false)
	{
		return false;
	}

	for (FMUEnforcementProbability& DropProbability : DropSelect.EnforcementProbabilities)
	{
		if (DropEnforcement.Num() >= ArrCount)
		{
			break;
		}
		
		float RandomValue = FMath::RandRange(0.f, 1.0f);

		bool bNeedToAdd = RandomValue < DropProbability.EnforcementProbability;
		bNeedToAdd &= DropEnforcement.Contains(DropProbability.EnforcementID) == false;
		if (bNeedToAdd == true)
		{
			DropEnforcement.Add(DropProbability.EnforcementID);
		}
	}

	return true;
}
