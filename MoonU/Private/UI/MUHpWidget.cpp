// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUHpWidget.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSetBase.h"

void UMUHpWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSetBase::GetCurrentHpAttribute()).AddUObject(this, &UMUHpWidget::OnHpChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSetBase::GetMaxHpAttribute()).AddUObject(this, &UMUHpWidget::OnMaxHpChanged);

		CurrentHealth = ASC->GetNumericAttribute(UMUCharacterAttributeSetBase::GetCurrentHpAttribute());
		CurrentMaxHealth = ASC->GetNumericAttribute(UMUCharacterAttributeSetBase::GetMaxHpAttribute());
	}

	UpdateHPBar_BP();
}

void UMUHpWidget::OnHpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentHealth = ChangeData.NewValue;
	UpdateHPBar_BP();
}

void UMUHpWidget::OnMaxHpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentMaxHealth = ChangeData.NewValue;
	UpdateHPBar_BP();
}
