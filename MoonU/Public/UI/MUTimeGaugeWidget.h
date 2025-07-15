// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGASWidget.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "MUTimeGaugeWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUTimeGaugeWidget : public UMUGASWidget
{
	GENERATED_BODY()
public :
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

protected:
	void OnTimeGaugeChanged(const FOnAttributeChangeData& IncomeData);
	
	void OnMaxTimeGaugeChanged(const FOnAttributeChangeData& IncomeData);

	void SetupPercentage();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnTimeGaugeChanged_BP();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time Gauge")
	float TimeGauge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time Gauge")
	float MaxTimeGauge;

	UPROPERTY( meta = (BindWidget) )
	TObjectPtr<class UProgressBar> PbTimeGauge;
};
