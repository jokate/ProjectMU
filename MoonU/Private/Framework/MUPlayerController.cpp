// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerController.h"

#include "Components/MUInputConsumeComponent.h"

AMUPlayerController::AMUPlayerController()
{
	CharacterType = ECharacterType::Player;
	InputConsumeComponent = CreateDefaultSubobject<UMUInputConsumeComponent>("InputConsumeComponent");
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
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn))
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

void AMUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMUPlayerController::SendInput(ECombatInputType CombatInput)
{
	if ( IsValid(InputConsumeComponent) == true )
	{
		InputConsumeComponent->SendInput(CombatInput);
	} 
}
