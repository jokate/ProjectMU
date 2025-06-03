// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Character/MUCharacterPlayer.h"
#include "Components/EnforcementComponent.h"
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

bool UMUFunctionLibrary::GetSkillData(UObject* Object, FName SkillID, FMUSkillData& OutSkillData)
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

	return DataTableSubsystem->GetSkillData(SkillID, OutSkillData);
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

	while (DropEnforcement.Num() < ArrCount)
	{
		for (FMUEnforcementProbability& DropProbability : DropSelect.EnforcementProbabilities)
		{
			UE_LOG(LogTemp, Log, TEXT("Drop ID : %d"), DropProbability.EnforcementID);
			// 목록에 다 찬 경우.
			if (DropEnforcement.Num() >= ArrCount)
			{
				break;
			}
		
			//전제조건에 대한 만족이 안된 경우.
			if (IsEnforcementPrerequisiteSatisfied(Object, DropProbability) == false)
			{ 
				continue;
			}

			//이미 스킬이 등록된 경우.
			if (IsSkillRegisteredToCharacter(Object, DropProbability.EnforcementID) == true)
			{
				UE_LOG(LogTemp, Log, TEXT("Already Registered"));
				continue;
			}
		
			float RandomValue = FMath::RandRange(0.f, 1.0f);

			bool bNeedToAdd = RandomValue < DropProbability.EnforcementProbability;
			bNeedToAdd &= DropEnforcement.Contains(DropProbability.EnforcementID) == false;
			if (bNeedToAdd == true)
			{
				DropEnforcement.Add(DropProbability.EnforcementID);
			}
		}
	}

	return true;
}

bool UMUFunctionLibrary::IsEnforcementPrerequisiteSatisfied(UObject* Object, FMUEnforcementProbability& InProbabilityData)
{
	if (IsValid(Object) == false)
	{
		return false;
	}

	ACharacter* Character = GetLocalPlayerCharacter(Object);
	AMUCharacterPlayer* CharacterPlayer = Cast<AMUCharacterPlayer>(Character);

	TArray<int32>& ProbabilityChecker = InProbabilityData.PrerequisiteID;
	ECheckOperationType CheckOperationType = InProbabilityData.CheckOperationType;
	bool bResult = true;
	if ( IsValid(CharacterPlayer) == true )
	{
		TArray<int32> EnforcementIDs;
		if (CharacterPlayer->GetEnforcementIDs(EnforcementIDs) == false)
		{
			return false;
		}
		
		switch (CheckOperationType)
		{
		case AND:
			{
				if (ProbabilityChecker.Num() > 0)
				{
					bResult = true;
					for ( int32 Probability : ProbabilityChecker)
					{
						bResult &= EnforcementIDs.Contains(Probability);	
					}	
				}
				break;	
			}
		case OR:
			{
				if (ProbabilityChecker.Num() > 0)
				{
					bResult = false;
					for ( int32 Probability : ProbabilityChecker)
					{
						bResult |= EnforcementIDs.Contains(Probability);	
					}	
				}
				break;
			}
		default :
			{
				break;
			}
		}
	}

	return bResult;
}

bool UMUFunctionLibrary::IsSkillRegisteredToCharacter(UObject* Object, int32 EnforcementID)
{
	ACharacter* Character = GetLocalPlayerCharacter(Object);
	if (IsValid(Character) == false)
	{
		return true;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	if (IsValid(ASC) == false)
	{
		return true;
	}

	FMUEnforcementData EnforcementData;
	if (GetEnforcementData(Object, EnforcementID, EnforcementData) == false )
	{
		return true;
	}

	if (EnforcementData.EnforcementType == Attribute )
	{
		return false;
	}
	
	FName SkillInfoData = EnforcementData.SkillID;
	FMUSkillData SkillData;
	if ( GetSkillData(Object, SkillInfoData, SkillData ) == false )
	{
		return false;
	}
	
	//이미 등록된 Ability인 경우에는 배제
	if (ASC->FindAbilitySpecFromClass(SkillData.NeedToRegAbility))
	{
		UE_LOG(LogTemp, Log, TEXT("IsSkillRegisteredToCharacter : Already Registered Ability"));
		return true;
	}

	return false;
}

UMUAbilitySystemComponent* UMUFunctionLibrary::GetAbilitySystemComponent(AActor* Owner)
{
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner);

	if (ASI == nullptr)
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

	if ( IsValid(ASC) == false)
	{
		return nullptr;		
	}

	UMUAbilitySystemComponent* MUASC = Cast<UMUAbilitySystemComponent>(ASC);

	return MUASC;
}
