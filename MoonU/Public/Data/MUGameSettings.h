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
#pragma endregion

private:
};
