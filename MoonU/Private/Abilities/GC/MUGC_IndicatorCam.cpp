// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GC/MUGC_IndicatorCam.h"

#include "Character/MUCharacterPlayer.h"


AMUGC_IndicatorCam::AMUGC_IndicatorCam()
{
	bAutoDestroyOnRemove = true;
}

void AMUGC_IndicatorCam::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AMUGC_IndicatorCam::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnActive_Implementation(MyTarget, Parameters);
	
	AMUCharacterPlayer* CharacterPlayer = Cast<AMUCharacterPlayer>(MyTarget);

	if ( IsValid(CharacterPlayer) == true )
	{
		CharacterPlayer->SetupCanLook( true );
	}

	return true;
}

bool AMUGC_IndicatorCam::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnRemove_Implementation(MyTarget, Parameters);

	AMUCharacterPlayer* CharacterPlayer = Cast<AMUCharacterPlayer>(MyTarget);

	if ( IsValid(CharacterPlayer) == true )
	{
		CharacterPlayer->SetupCanLook( false );
	}
	
	return true;
}


