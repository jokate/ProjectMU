// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Data/MUEnum.h"
#include "GameFramework/PlayerController.h"
#include "MUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public :
	AMUPlayerController();

	void BeginPlay() override;
	
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UPROPERTY()
	FGenericTeamId TeamId;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECharacterType> CharacterType;
};
