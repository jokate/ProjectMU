// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillInputTarget.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USkillInputTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE( FOnSkillActivate );
DECLARE_MULTICAST_DELEGATE( FOnSkillDeactivate );

class MOONU_API ISkillInputTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FOnSkillActivate& GetActivationSkillEvent() = 0;
	virtual FOnSkillDeactivate& GetDeactivationSkillEvent() = 0;
};
