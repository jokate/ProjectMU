// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_BoxTrace.h"

#include "Components/BoxComponent.h"


// Sets default values
AMUTA_BoxTrace::AMUTA_BoxTrace()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AMUTA_BoxTrace::SetupBoxExtent(FVector InBoxExtent)
{
	BoxComponent->SetBoxExtent(InBoxExtent);
}


