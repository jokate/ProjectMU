﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUTA_Trace.h"
#include "MUTA_DashAttackTrace.generated.h"

UCLASS()
class MOONU_API AMUTA_DashAttackTrace : public AMUTA_Trace
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTA_DashAttackTrace();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TraceStart() override; 
};
