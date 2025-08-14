// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MUEnforcementSceneWidget.generated.h"

/**
 * 
 */


class UMUTopMenuWidget;
class UMUSkillTreeWidget;

UCLASS()
class MOONU_API UMUEnforcementSceneWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

public :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMUSkillTreeWidget> SkillTreeWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMUTopMenuWidget> MenuWidget;
	
};
