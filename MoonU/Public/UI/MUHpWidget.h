// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGASWidget.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "MUHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUHpWidget : public UMUGASWidget
{
	GENERATED_BODY()
public :
	
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

protected :
	virtual void OnHpChanged(const FOnAttributeChangeData& ChangeData);
	virtual void OnMaxHpChanged(const FOnAttributeChangeData& ChangeData);

	virtual void SetupPercent();
	
protected :
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHPBar_BP();

	UPROPERTY( meta = (BindWidget))
	TObjectPtr<class UProgressBar> PbHpBar;
	
	UPROPERTY( meta = (BindWidget))
	TObjectPtr<class UTextBlock> HpText;
	
protected :
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentMaxHealth = 0.1f;
};
