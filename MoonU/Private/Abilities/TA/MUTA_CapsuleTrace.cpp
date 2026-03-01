// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_CapsuleTrace.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AMUTA_CapsuleTrace::AMUTA_CapsuleTrace()
{
	CapsuleTrace = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleTrace"));
	CapsuleTrace->SetupAttachment(GetRootComponent());
}

void AMUTA_CapsuleTrace::SetupCapsule(float HalfHeight, float Radius)
{
	CapsuleTrace->SetCapsuleRadius(Radius);
	CapsuleTrace->SetCapsuleHalfHeight(HalfHeight);
}

