﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUTimeGaugeWidget.h"

#include "Attribute/MUCharacterAttributeSet.h"
#include "Attribute/MUTimewinderAttribute.h"

void UMUTimeGaugeWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);
	
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetCurrentTimeGaugeAttribute()).AddUObject(this, &UMUTimeGaugeWidget::OnTimeGaugeChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetMaxTimeGaugeAttribute()).AddUObject(this, &UMUTimeGaugeWidget::OnMaxTimeGaugeChanged);

		TimeGauge = ASC->GetNumericAttribute(UMUCharacterAttributeSetBase::GetCurrentHpAttribute());
		MaxTimeGauge = ASC->GetNumericAttribute(UMUCharacterAttributeSetBase::GetMaxHpAttribute());
	}
}

void UMUTimeGaugeWidget::OnTimeGaugeChanged(const FOnAttributeChangeData& IncomeData)
{
	TimeGauge = IncomeData.NewValue;
	OnTimeGaugeChanged_BP();
}

void UMUTimeGaugeWidget::OnMaxTimeGaugeChanged(const FOnAttributeChangeData& IncomeData)
{
	MaxTimeGauge = IncomeData.NewValue;
	OnTimeGaugeChanged_BP();
}
