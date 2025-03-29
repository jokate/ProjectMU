// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MUEnum.generated.h"

UENUM(BlueprintType)
enum EVelocityDirection
{
	Frontward,
	Backward,
	Left,
	Right,
	FrontwardLeft,
	BackwardLeft,
	FrontwardRight,
	BackwardRight
};

UENUM(BlueprintType)
enum EMotionWarpType
{
	TranslationAndRotation,
	TranslationOnly,
	RotationOnly
};

UENUM(BlueprintType)
enum EMovementSpeedEnum
{
	NoMove,
	Walking,
	
	Sprinting
};

UENUM(BlueprintType)
enum EPerceptionType
{
	InValid,
	Sight,
	Damage,
	Hearing
};

UENUM(BlueprintType)
enum ECharacterType
{
	Neutral = 0,
	Player,
	AI,
	BossAI,
};

UENUM(BlueprintType)
enum EEffectApplicationMode
{
	Self,
	Target,
};

UENUM(BlueprintType)
enum EGASInputFunctionalType
{
	Pressed,
	Released,
	Invalid
};

UENUM(BlueprintType)
enum EEnforcementType
{
	Attribute,
	SkillOpen,
	SkillEnforcement,
	MAX
};

UENUM(BlueprintType)
enum ECheckOperationType
{
	AND,
	OR,
	NOR
};

UENUM(BlueprintType)
enum ETargetActivationType
{
	NoTarget,
	Location,
	Actor
};

UENUM(BlueprintType)
enum class ESkillSlotType : uint8
{
	NONE,
	SkillSlot_1,
	SkillSlot_2,
	SkillSlot_3
};

UENUM( BlueprintType )
enum class ESkillCastingType : uint8
{
	NONE,
	Instant,
	Indicator
};