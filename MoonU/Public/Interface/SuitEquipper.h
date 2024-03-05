﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SuitEquipper.generated.h"

DECLARE_DELEGATE_OneParam(FSuitDelegate, bool);

// This class does not need to be modified.
UINTERFACE()
class USuitEquipper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ISuitEquipper
{
	GENERATED_BODY()
	
public:
	virtual FSuitDelegate& GetSuitEquipEvent() = 0;
	
	virtual FSuitDelegate& GetHeadEquipEvent() = 0;

	virtual bool GetSuitEquipped() const = 0;

	virtual bool GetHeadEquipped() const = 0;

	virtual void SetSuitEquipped(bool InSuitEquip) = 0;
	
	virtual void SetHeadEquipped(bool InSuitEquip) = 0;
};
