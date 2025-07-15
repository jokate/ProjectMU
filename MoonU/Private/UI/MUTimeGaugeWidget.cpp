// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUTimeGaugeWidget.h"

#include "Attribute/MUCharacterAttributeSet.h"
#include "Attribute/MUTimewinderAttribute.h"
#include "Components/ProgressBar.h"

void UMUTimeGaugeWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);
	
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetCurrentTimeGaugeAttribute()).AddUObject(this, &UMUTimeGaugeWidget::OnTimeGaugeChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetMaxTimeGaugeAttribute()).AddUObject(this, &UMUTimeGaugeWidget::OnMaxTimeGaugeChanged);

		TimeGauge = ASC->GetNumericAttribute(UMUTimewinderAttribute::GetCurrentTimeGaugeAttribute());
		MaxTimeGauge = ASC->GetNumericAttribute(UMUTimewinderAttribute::GetMaxTimeGaugeAttribute());
	}
}

void UMUTimeGaugeWidget::OnTimeGaugeChanged(const FOnAttributeChangeData& IncomeData)
{
	TimeGauge = IncomeData.NewValue;
	SetupPercentage();
}

void UMUTimeGaugeWidget::OnMaxTimeGaugeChanged(const FOnAttributeChangeData& IncomeData)
{
	MaxTimeGauge = IncomeData.NewValue;
	SetupPercentage();
}

void UMUTimeGaugeWidget::SetupPercentage()
{
	if ( IsValid(PbTimeGauge) == true )
	{
		PbTimeGauge->SetPercent( TimeGauge / MaxTimeGauge ); 
	}
}

