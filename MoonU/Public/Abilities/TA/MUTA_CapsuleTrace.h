// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUTA_Trace.h"
#include "MUTA_CapsuleTrace.generated.h"

class UCapsuleComponent;

UCLASS()
class MOONU_API AMUTA_CapsuleTrace : public AMUTA_Trace
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTA_CapsuleTrace();
	void SetupCapsule(float HalfHeight, float Radius);
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleTrace;
	
};
