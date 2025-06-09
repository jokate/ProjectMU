// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUEnum.h"
#include "UObject/Interface.h"
#include "MotionWarpTarget.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMotionWarpTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IMotionWarpTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class UMotionWarpingComponent* GetMotionWarpComponent() = 0; 
	
	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f) = 0;

	virtual void ReleaseMotionWarp(const FName InName) = 0;

	virtual void SetMotionWarpToCursorDirection( const FName TargetName, EMotionWarpType InMotionWarpType, const FVector& TargetLocation, const FRotator& TargetRotation ) {};
};
