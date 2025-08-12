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

int32 UMUEnforcementSubsystem::GetAllocatedAttribute(const int32 CharacterID, const FName& AttributeSlot)
{
	if ( CharacterEnforcementAllocated.Contains( CharacterID ) == false )
	{
		return -1;
	}

	const FMUEnforcementAllocate& CharacterEnforcement = CharacterEnforcementAllocated[CharacterID];

	const TMap<FName, int32>& AttributeMap = CharacterEnforcement.AttributeMap;

	if ( AttributeMap.Contains( AttributeSlot ) == false )
	{
		return -1;
	}

	return AttributeMap[AttributeSlot];
}

int32 UMUEnforcementSubsystem::GetAllocatedSkill(const int32 CharacterID, const ESkillSlotType SkillSlotType)
{
	if ( CharacterEnforcementAllocated.Contains( CharacterID ) == false )
	{
		return -1;
	}

	const FMUEnforcementAllocate& CharacterEnforcement = CharacterEnforcementAllocated[CharacterID];

	const TMap<ESkillSlotType, int32>& SkillSlotMap = CharacterEnforcement.AllocatedSkillID;

	if (SkillSlotMap.Contains(SkillSlotType) == false )
	{
		return -1;
	}

	return SkillSlotMap[SkillSlotType];
}
