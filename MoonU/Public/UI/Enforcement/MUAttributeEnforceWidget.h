// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUEnforcementWidget.h"
#include "MUAttributeEnforceWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAttributeEnforceWidget : public UMUEnforcementWidget
{
	GENERATED_BODY()

public :
	virtual void InitializeValue( int32 InCharacterID, FName InSkillSlotName );

	virtual void SetupWidgetInfo() override;

public :
	UPROPERTY( BlueprintReadOnly )
	FName AttributeSlotName;
};
