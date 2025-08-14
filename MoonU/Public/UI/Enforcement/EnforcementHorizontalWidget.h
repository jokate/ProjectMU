// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/DataTable/MUWidgetData.h"
#include "EnforcementHorizontalWidget.generated.h"

class UMUEnforcementWidget;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class MOONU_API UEnforcementHorizontalWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void InitializeWidget( int32 CharacterID,
		FAttributeEnforcementSlotData& EnforcementWidgetData, TSubclassOf<UUserWidget> AttributeWidgetClass);
	
public :
	UPROPERTY( BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> EnforcementHorizontal;
	
	UPROPERTY( EditDefaultsOnly )
	float PaddingValue = 50.f;
};
