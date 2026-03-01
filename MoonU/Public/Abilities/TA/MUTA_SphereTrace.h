// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUTA_Trace.h"
#include "MUTA_SphereTrace.generated.h"

class USphereComponent;

UCLASS()
class MOONU_API AMUTA_SphereTrace : public AMUTA_Trace
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTA_SphereTrace();

	void SetupRadius(float InRadius);
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereTrace;
};
