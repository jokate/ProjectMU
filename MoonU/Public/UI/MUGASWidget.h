// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Blueprint/UserWidget.h"
#include "MUGASWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGASWidget : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public :
	virtual void SetAbilitySystemComponent(AActor* InOwner);

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;
};
