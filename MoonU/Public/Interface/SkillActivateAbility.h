// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUEnum.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "SkillActivateAbility.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USkillActivateAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ISkillActivateAbility
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ActivateSkill() = 0;
	virtual void CancelSkill() = 0;
	
	virtual void SetComboPressed() {}
	virtual bool IsComboPressed() const { return false; }
	virtual void ResetComboPressed() {}

	virtual void SetMontageSection(FName MontageSectionName) {}
	virtual void ReceivePressedTag(const FGameplayTag& InputTag) {}
	virtual void ReceiveReleasedTag(const FGameplayTag& InputTag) {}
 
#pragma region Getter

	virtual FName GetSkillID()
	{
		return NAME_None;
	}

	virtual FTransform GetTargetTransform()
	{
		return FTransform();
	}

	virtual ESkillType GetSkillType() const
	{
		return ESkillType::None;
	}

	virtual bool IsSkillCombo() const
	{
		return GetSkillType() == ESkillType::Combo;
	}

	virtual bool IsSkillInstant() const
	{
		return GetSkillType() == ESkillType::Instant;
	}

	virtual bool IsSkillIndicator() const
	{
		return GetSkillType() == ESkillType::Indicator;
	}

	virtual bool IsSkillCharge() const
	{
		return GetSkillType() == ESkillType::Charge;
	}
#pragma endregion Getter
};
