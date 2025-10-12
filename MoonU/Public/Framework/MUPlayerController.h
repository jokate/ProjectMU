// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Data/MUEnum.h"
#include "GameFramework/PlayerController.h"
#include "MUPlayerController.generated.h"

class UMUInputConsumeComponent;
/**
 * 
 */
UCLASS()
class MOONU_API AMUPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public :
	AMUPlayerController();

	virtual void BeginPlay() override;
	
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

#pragma region IGenericTeamAgentInterface
	
	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
#pragma endregion IGenericTeamAgentInterface

	virtual void SetupInputComponent() override;

	virtual void SendInput(ECombatInputType CombatInput);
	
public : 
	UPROPERTY()
	FGenericTeamId TeamId;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECharacterType> CharacterType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input Consumer")
	TObjectPtr<UMUInputConsumeComponent> InputConsumeComponent;
};
