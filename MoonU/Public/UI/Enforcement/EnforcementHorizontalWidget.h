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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMemberClicked, FName, SlotName);

UCLASS()
class MOONU_API UEnforcementHorizontalWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void InitializeWidget( int32 CharacterID,
		FAttributeEnforcementSlotData& EnforcementWidgetData, TSubclassOf<UUserWidget> AttributeWidgetClass);

	UFUNCTION()
	virtual void MemberClickedCallback(FName SlotName);
	
public :
	UPROPERTY( BlueprintAssignable, BLueprintCallable )
	FOnMemberClicked OnMemberClicked;
	
public :
	UPROPERTY( BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> EnforcementHorizontal;
	
	UPROPERTY( EditDefaultsOnly )
	float PaddingValue = 50.f;
};
