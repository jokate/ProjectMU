// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_ActivateTagWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_ActivateTagWidget : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_ActivateTagWidget* CreateTask( UGameplayAbility* InAbility, FGameplayTag InWidgetTag );

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;
	
public :
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> TagWidget;
	UPROPERTY()
	FGameplayTag WidgetTag;
};
