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

	// 코스트 소비
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

	// Enforce에 따른 Cost 소비/
}

void UMUEnforcementSubsystem::UseEnforcementCost(const int32 CharacterID, const int32 EnforcementCost)
{
	if ( CharacterEnforcementCost.Contains( CharacterID ) == false )
	{
		return;
	}

	CharacterEnforcementCost[CharacterID] -= EnforcementCost;

	//이벤트 호출 필요.
	if ( OnEnforcementUpdated.IsBound() == true )
	{
		OnEnforcementUpdated.Broadcast();
	}
}

void UMUEnforcementSubsystem::OnPlayerLevelUp()
{
	// 캐릭터에 대한 언락 여부기준으로 봐야 할 것으로 보임.
	for ( TPair<int32, int32>& EnforceCount : CharacterEnforcementCost )
	{
		EnforceCount.Value++;
	}

	if ( OnEnforcementUpdated.IsBound() == true )
	{
		OnEnforcementUpdated.Broadcast();
	}
}
