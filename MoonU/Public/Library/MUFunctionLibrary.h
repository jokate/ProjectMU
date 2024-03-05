// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MUFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable)
	static ACharacter* GetLocalPlayerCharacter(UObject* WorldObject);
};
