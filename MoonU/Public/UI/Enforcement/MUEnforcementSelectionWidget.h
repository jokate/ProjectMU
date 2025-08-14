// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MUEnum.h"
#include "Data/MUStruct.h"
#include "MUEnforcementSelectionWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnEnforcementSelected );

UCLASS()
class MOONU_API UMUEnforcementSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void InitializeValue( EEnforcementType InEnforcementType, FMUEnforcementSelection& InEnforcementData );

	UFUNCTION()
	virtual void OnSelectedButton();

	virtual void SetupWidget();

public :
	UPROPERTY( BlueprintCallable, BlueprintAssignable )
	FOnEnforcementSelected OnEnforcementSelected;
	
public :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> EnforcementImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> EnforcementTitleText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> EnforcementDescriptionText;

	UPROPERTY( BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> SelectionButton;

public :
	UPROPERTY( BlueprintReadOnly )
	TEnumAsByte<EEnforcementType> EnforcementType;

	UPROPERTY( BlueprintReadOnly )
	FMUEnforcementSelection EnforcementData;
};
