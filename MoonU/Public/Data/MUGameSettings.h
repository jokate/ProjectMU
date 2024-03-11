// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MUGameSettings.generated.h"

/**
 * 
 */
static TObjectPtr<UMUGameSettings> GameSettingInstance;

UCLASS(Config = Game)
class MOONU_API UMUGameSettings : public UObject
{
	GENERATED_BODY()
	
public :

	static const UMUGameSettings* Get();

#pragma region On Gameplay
	UPROPERTY(Config)
	FGameplayTag SuitInteractionTag;

	UPROPERTY(Config)
	FGameplayTag HelmetInteractionTag;
#pragma endregion

#pragma region UI GameplayTags
	UPROPERTY(Config)
	FGameplayTag HUDGameplayTag;

	UPROPERTY(Config)
	FGameplayTag InventoryGameplayTag;

	UPROPERTY(Config)
	FGameplayTag StorageGameplayTag;
#pragma endregion

#pragma region Equipment Upgrade Tag
	UPROPERTY(Config)
	FGameplayTag SuitOxygenUpgradeTag;

	UPROPERTY(Config)
	FGameplayTag SuitRecoveryUpgradeTag;
#pragma endregion

#pragma region Item Tag
	UPROPERTY(Config)
	FGameplayTag ComsumableItemTag;

	UPROPERTY(Config)
	FGameplayTag EquippableItemTag;

	UPROPERTY(Config)
	FGameplayTag CraftableItemTag;
#pragma endregion 
	
#pragma region Input Action Tag
	UPROPERTY(Config)
	FGameplayTag MoveInputTag;

	UPROPERTY(Config)
	FGameplayTag LookInputTag;

	UPROPERTY(Config)
	FGameplayTag JumpInputTag;

	UPROPERTY(Config)
	FGameplayTag InteractInputTag;

	UPROPERTY(Config)
	FGameplayTag InventoryUITag;

	UPROPERTY(Config)
	FGameplayTag SprintInputTag;

	UPROPERTY(Config)
	FGameplayTag UICloseTag;
#pragma endregion
private:
};
