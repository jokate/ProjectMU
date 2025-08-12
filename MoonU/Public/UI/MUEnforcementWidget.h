// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MUEnforcementWidget.generated.h"

/**
 * 
 */
class UButton;
class UImage;

UCLASS()
class MOONU_API UMUEnforcementWidget : public UUserWidget
{
	GENERATED_BODY()

public : 
	virtual void NativeConstruct() override;

public :
	virtual void SetupWidgetInfo();

	UFUNCTION( BlueprintNativeEvent )
	void OnSelectionButtonClicked();
	virtual void OnSelectionButtonClicked_Implementation();
public :

	UPROPERTY( BlueprintReadOnly )
	int32 AllocatedEnforcementID = 0;
	
	UPROPERTY( BlueprintReadOnly )
	int32 CharacterID;
	
	UPROPERTY( BlueprintReadWrite, meta = (BindWidget) )
	TObjectPtr<UButton> SelectionButton;

	UPROPERTY( BlueprintReadWrite, meta = (BindWidget) )
	TObjectPtr<UImage> PortraitImage;
};
