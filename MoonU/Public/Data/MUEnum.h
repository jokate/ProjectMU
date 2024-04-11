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
