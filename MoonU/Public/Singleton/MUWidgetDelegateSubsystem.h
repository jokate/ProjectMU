// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MUWidgetDelegateSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, Level);

UCLASS()
class MOONU_API UMUWidgetDelegateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintAssignable)
	FOnLevelChanged OnLevelChanged;
};
