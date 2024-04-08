// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public :
	AMUPlayerState();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;
};
