// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUEnum.h"
#include "Data/MUStruct.h"

#include "MUEnforcementManageComponent.generated.h"

/*
 * Purpose : GM에 붙어서, 강화 매니징을 한다.
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCharacterChanged, const int32, CharacterID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCharacterAttributeAdded, const int32, CharacterID, const int32, EnforcementID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnCharacterSkillAdded, const int32, CharacterID, ESkillSlotType, SkillSlotType, const int32, EnforcementID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnEnforcementUpdated );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUEnforcementManageComponent : public UActorComponent
{
	GENERATED_BODY()

public :
	void EnforceAttributeAdded( const int32 CharacterID, FName& EnforcementSlotName, const int32 EnforcementID );
	
	void EnforceSkillAdded( const int32 CharacterID, ESkillSlotType SkillSlotType, const int32 EnforcementID );

	void UseEnforcementCost( const int32 CharacterID, const int32 EnforcementCost );

	void OnPlayerLevelUp();

	UFUNCTION( BlueprintPure )
	int32 GetLevelEnforcementCost( const int32 CharacterID ) { return CharacterEnforcementCost.FindOrAdd(CharacterID); }

	UFUNCTION( BlueprintPure )
	int32 GetAllocatedAttribute( const int32 CharacterID, const FName& AttributeSlot );

	UFUNCTION( BlueprintPure )
	int32 GetAllocatedSkill( const int32 CharacterID, const ESkillSlotType SkillSlotType );
	public :
		UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterChanged	OnCharacterChanged;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterAttributeAdded OnCharacterAttributeAdded;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterSkillAdded OnCharacterSkillAdded;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnEnforcementUpdated OnEnforcementUpdated;
	
	public :
		UPROPERTY( BlueprintReadOnly )
	TMap<int32, FMUEnforcementAllocate> CharacterEnforcementAllocated;

	UPROPERTY( BlueprintReadOnly )
	TMap<int32, int32> CharacterEnforcementCost;
};
