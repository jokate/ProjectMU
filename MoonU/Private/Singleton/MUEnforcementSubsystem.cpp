// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/MUEnforcementSubsystem.h"

void UMUEnforcementSubsystem::EnforceAttributeAdded(const int32 CharacterID, FName& EnforcementSlotName,
	const int32 EnforcementID)
{
	FMUEnforcementAllocate& AllocatedData = CharacterEnforcementAllocated.FindOrAdd( CharacterID );

	TMap<FName, int32>& AllocatedAttributeMap = AllocatedData.AttributeMap;
	AllocatedAttributeMap.Emplace( EnforcementSlotName, EnforcementID );

	if ( OnCharacterAttributeAdded.IsBound() == true )
	{
		OnCharacterAttributeAdded.Broadcast( CharacterID, EnforcementID );
	}
}

void UMUEnforcementSubsystem::EnforceSkillAdded(const int32 CharacterID, ESkillSlotType SkillSlotType, const int32 EnforcementID)
{
	FMUEnforcementAllocate& AllocatedData = CharacterEnforcementAllocated.FindOrAdd( CharacterID );

	TMap<ESkillSlotType, int32>& AllocatedSkillID = AllocatedData.AllocatedSkillID;
	
	AllocatedSkillID.Emplace( SkillSlotType, EnforcementID );

	if ( OnCharacterSkillAdded.IsBound() == true )
	{
		OnCharacterSkillAdded.Broadcast( CharacterID, SkillSlotType, EnforcementID );
	}
}
