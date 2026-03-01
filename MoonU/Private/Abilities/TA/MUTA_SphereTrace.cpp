// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_SphereTrace.h"

#include "Components/SphereComponent.h"


// Sets default values
AMUTA_SphereTrace::AMUTA_SphereTrace()
{
	SphereTrace = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrace"));
	SphereTrace->SetupAttachment(RootComponent);
}

void AMUTA_SphereTrace::SetupRadius(float InRadius)
{
	SphereTrace->SetSphereRadius(InRadius);
}