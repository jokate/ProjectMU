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
	RotationOnly,
	NoneMotionWarp,
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
	SkillSlot_3,

	// 페인터 전용 스킬 타입
	Paint_1,
	Paint_2,
	Paint_3,
	Paint_4,
	Paint_5,
	Paint_6,
	Paint_7,
	Paint_8,
	Paint_9,
	Paint_10,
};

UENUM( BlueprintType )
enum class ESkillCastingType : uint8
{
	NONE,
	Instant,
	Indicator
};

UENUM( BlueprintType )
enum class ESkillIndicatorType : uint8
{
	NONE,
	LINEAR,
	CIRCULAR
};

UENUM( BlueprintType )
enum class EBlendSpaceType : uint8
{
	NONE,
	OneDim,
	TwoDims,
};

UENUM( BLueprintType )
enum class ECombatInputType : uint8
{
	None,
	Jump,
	BasicAttack,
	Defense,
};
