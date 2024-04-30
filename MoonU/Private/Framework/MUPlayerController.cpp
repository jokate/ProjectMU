// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerController.h"

AMUPlayerController::AMUPlayerController()
{
	CharacterType = ECharacterType::Player;
}

void AMUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetGenericTeamId(FGenericTeamId(CharacterType));
}

void AMUPlayerController::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	TeamId = TeamID;
}

FGenericTeamId AMUPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

ETeamAttitude::Type AMUPlayerController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			const FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

			if (OtherTeamID.GetId() == ECharacterType::Neutral)
			{
				return ETeamAttitude::Neutral;
			}
			
			if (OtherTeamID.GetId() != GetGenericTeamId())
			{
				return ETeamAttitude::Hostile;
			}

			return ETeamAttitude::Friendly;
		}
	}

	return ETeamAttitude::Neutral;
}