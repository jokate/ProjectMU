// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUEnforcementWidget.h"
#include "Data/MUEnum.h"
#include "MUSkillSlotWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MOONU_API UMUSkillSlotWidget : public UMUEnforcementWidget
{
	GENERATED_BODY()

public :
	virtual void OnSelectionButtonClicked_Implementation() override;
	
public :
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	ESkillSlotType SkillSlotType;
};
