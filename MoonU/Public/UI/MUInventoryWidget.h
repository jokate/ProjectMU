// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUWidget.h"
#include "Blueprint/UserWidget.h"
#include "MUInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUInventoryWidget : public UMUWidget
{
	GENERATED_BODY()

public :
	void OnInventoryUpdated();

protected :
	UFUNCTION(BlueprintImplementableEvent)
	void OnInventoryUpdated_BP();
};
