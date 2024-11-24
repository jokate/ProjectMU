// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataTable/MUData.h"
#include "Interface/InteractableTarget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MUFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable)
	static ACharacter* GetLocalPlayerCharacter(UObject* WorldObject);

	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetInteractableGameplayTag(UObject* InteractableTarget);

	UFUNCTION(BlueprintCallable)
	static UGameInstance* GetGameInstance(UObject* Object);

	UFUNCTION(BlueprintCallable)
	static bool GetInputMapperData(UObject* Object, int32 InCharacterID, FMUInputMapper& InputMapperData);

	UFUNCTION(BlueprintCallable)
	static bool GetCharacterInfoData(UObject* Object, int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo);

	UFUNCTION(BlueprintCallable)
	static bool GetEnforcementData(UObject* Object, int32 EnforcementID, FMUEnforcementData& OutEnforcementData);

	UFUNCTION( BlueprintCallable )
	static bool BindInputActionByTag( class AMUCharacterPlayer* CharacterPlayer, int32 CharacterID, FTagByInput& TagByInput);
};
