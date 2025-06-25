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
class UMUAbilitySystemComponent;
UCLASS()
class MOONU_API UMUFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintPure)
	static ACharacter* GetLocalPlayerCharacter(UObject* WorldObject);

	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetInteractableGameplayTag(UObject* InteractableTarget);

	UFUNCTION(BlueprintCallable)
	static UGameInstance* GetGameInstance(UObject* Object);

	UFUNCTION( BlueprintCallable )
	static bool BindInputActionByTag( class AMUCharacterPlayer* CharacterPlayer, int32 CharacterID, FTagByInput& TagByInput);

	UFUNCTION( BlueprintPure )
	static bool GetEnforcementDropTable(UObject* Object, int32 Level, int32 ArrCount, TSet<int32>& DropEnforcement);

	UFUNCTION( BlueprintPure )
	static bool IsEnforcementPrerequisiteSatisfied(UObject* Object, FMUEnforcementProbability& InProbabilityData);

	UFUNCTION( BlueprintPure )
	static bool IsSkillRegisteredToCharacter(UObject* Object, int32 EnforcementID);

	UFUNCTION( BlueprintCallable )
	static UMUAbilitySystemComponent* GetAbilitySystemComponent( AActor* Owner );

	UFUNCTION( BlueprintCallable )
	static class UInputConfig* GetInputConfigByOwner( AActor* Owner );
	
#pragma region DataGetter
	UFUNCTION(BlueprintPure)
	static bool GetInputMapperData(UObject* Object, int32 InCharacterID, FMUInputMapper& InputMapperData);

	UFUNCTION(BlueprintPure)
	static bool GetCharacterInfoData(UObject* Object, int32 InCharacterID, FMUCharacterInfo& OutCharacterInfo);

	UFUNCTION(BlueprintPure)
	static bool GetEnforcementData(UObject* Object, int32 EnforcementID, FMUEnforcementData& OutEnforcementData);

	UFUNCTION(BlueprintPure)
	static bool GetEnforcementDropData(UObject* Object, int32 Level, FMUEnforcementDropSelect& OutEnforcementDropSelect);

	UFUNCTION( BlueprintPure )
	static bool GetSkillData( UObject* Object, FName SkillID, FMUSkillData& OutSkillData);

	UFUNCTION( BlueprintPure )
	static bool GetStageInfoData( UObject* Object, FName StageInfoName, FMUStageInfo& OutStageInfo );

	UFUNCTION( BlueprintPure )
	static bool GetStageData( UObject* Object, FName StageName, FMUStageData& OutStageData );

	UFUNCTION( BlueprintPure )
	static bool GetMonsterData( UObject* Object, FName SpawnerName, FMUMonsterSpawnData& OutSpawnerData );
#pragma endregion
};
