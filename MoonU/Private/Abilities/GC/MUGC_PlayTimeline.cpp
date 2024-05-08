// Fill out your copyright notice in the Description page of Project Settings.

 
#include "Abilities/GC/MUGC_PlayTimeline.h"

#include "Components/TimelineComponent.h"

AMUGC_PlayTimeline::AMUGC_PlayTimeline()
{
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>("TimelineComponent");
}

void AMUGC_PlayTimeline::BeginPlay()
{
	Super::BeginPlay();

	if (TimelineCurve)
	{
		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindDynamic(this, &AMUGC_PlayTimeline::OnValueChanged);
		TimelineComponent->AddInterpFloat(TimelineCurve, TimelineFloat);
	} 
}

bool AMUGC_PlayTimeline::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	TimelineComponent->Play();

	return false;
}

bool AMUGC_PlayTimeline::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	TimelineComponent->Reverse();

	FOnTimelineEvent Event;
	Event.BindDynamic(this, &AMUGC_PlayTimeline::OnFinishedTimeline);
	TimelineComponent->SetTimelineFinishedFunc(Event);
	
	return false;
}

void AMUGC_PlayTimeline::OnFinishedTimeline()
{
	Destroy();
}


void AMUGC_PlayTimeline::OnValueChanged(float InValue)
{
	OnValueChanged_BP(InValue);
}

