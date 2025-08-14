// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MUEnum.h"
#include "MUEnforcementSceneWidget.generated.h"

/**
 * 
 */


class UMUEnforcementSelectionCanvas;
class UMUTopMenuWidget;
class UMUSkillTreeWidget;

UCLASS()
class MOONU_API UMUEnforcementSceneWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void AttributeEnforcementClickedCallback( FName SlotName );

	UFUNCTION()
	virtual void SkillEnforcementClickedCallback( ESkillSlotType SlotType );

public :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMUSkillTreeWidget> SkillTreeWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMUTopMenuWidget> MenuWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMUEnforcementSelectionCanvas> EnforcementSelectionWidget;
};
