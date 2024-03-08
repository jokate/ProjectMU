// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MUWidgetInterface.generated.h"

/**
 * 
 */
// This class does not need to be modified.
UINTERFACE()
class UMUWidgetInterface : public UInterface
{
	GENERATED_BODY()
};


class MOONU_API IMUWidgetInterface
{
	GENERATED_BODY()

public :
	virtual void OnWidgetShow() = 0;

	virtual void OnWidgetHide() = 0;

	virtual void OnWidgetUpdated() = 0;

	virtual void OnWidgetUpdatedByActor(AActor* InActor) = 0;
};
