// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUEnum.h"
#include "UObject/Interface.h"
#include "SkillManager.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USkillManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ISkillManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddSkillSlot( ESkillSlotType SkillSlotType, FName SkillID ) = 0;

	virtual void RemoveSkillSlot( ESkillSlotType SkillSlotType ) = 0 ;

	virtual const FName GetSkillIDBySlot( ESkillSlotType SkillSlot ) = 0;;
};
