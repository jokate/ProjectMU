// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/DataTable/MUWidgetData.h"
#include "MUTopMenuButton.generated.h"

class UTextBlock;
class FOnButtonClickedEvent;
class UButton;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnClickedTopMenuButton, FName, TargetName );
UCLASS()
class MOONU_API UMUTopMenuButton : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void Initialize( FTopMenuItem InTopMenuItem);

	UFUNCTION()
	void OnClickedButtonCallback();

public :
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnClickedTopMenuButton OnClickedButton;
	
public :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> TopMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TopMenuText;

	UPROPERTY(BlueprintReadOnly)
	FTopMenuItem TopMenuItem;
};
