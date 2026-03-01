// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUTA_Trace.h"
#include "MUTA_BoxTrace.generated.h"

class UBoxComponent;

UCLASS()
class MOONU_API AMUTA_BoxTrace : public AMUTA_Trace
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTA_BoxTrace();

	void SetupBoxExtent(FVector InBoxExtent);
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxComponent;
};
