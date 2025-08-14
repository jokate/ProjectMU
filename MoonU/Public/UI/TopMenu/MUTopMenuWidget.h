// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MUTopMenuWidget.generated.h"

class UHorizontalBox;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnChangedTopMenu, FName, TargetName );

UCLASS()
class MOONU_API UMUTopMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnTopMenuChanged(FName InName);
	
public : 
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable )
	FOnChangedTopMenu OnChangedTopMenu;
	
public :
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> TopMenuHorizontalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TopMenuName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PaddingValue = 30.f;
};
