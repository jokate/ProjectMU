// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual bool GetSuitEquipped() const = 0;

	virtual void EquipSuit(AActor* SuitEntity) = 0;

	virtual AActor* UnEquipSuit() = 0;
};
