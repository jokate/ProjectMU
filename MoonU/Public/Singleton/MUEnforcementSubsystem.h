// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUEnum.h"
#include "Data/MUStruct.h"
#include "MUEnforcementSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCharacterChanged, const int32, CharacterID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCharacterAttributeAdded, const int32, CharacterID, const int32, EnforcementID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnCharacterSkillAdded, const int32, CharacterID, ESkillSlotType, SkillSlotType, const int32, EnforcementID );

UCLASS()
class MOONU_API UMUEnforcementSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public :
	void EnforceAttributeAdded( const int32 CharacterID, FName& EnforcementSlotName, const int32 EnforcementID );
	
	void EnforceSkillAdded( const int32 CharacterID, ESkillSlotType SkillSlotType, const int32 EnforcementID );

public :
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterChanged	OnCharacterChanged;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterAttributeAdded OnCharacterAttributeAdded;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnCharacterSkillAdded OnCharacterSkillAdded;
	
public :
	UPROPERTY( BlueprintReadOnly )
	TMap<int32, FMUEnforcementAllocate> CharacterEnforcementAllocated;
};
