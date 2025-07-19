// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "InputTriggers.h"
#include "MUAT_WaitTriggerInput.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInputPressed );

UCLASS()
class MOONU_API UMUAT_WaitTriggerInput : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	static UMUAT_WaitTriggerInput* CreateTask( UGameplayAbility* OwningAbility, FGameplayTag InputGameplayTag, ETriggerEvent TriggerEvent );

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	UFUNCTION()
	void OnInputPressed();

	void ResetInput();
	
public :
	UPROPERTY()
	FGameplayTag GameplayTag;

	UPROPERTY()
	ETriggerEvent TriggerEvent;
	
	UPROPERTY( BlueprintAssignable )
	FOnInputPressed InputPressedCallback;
};
