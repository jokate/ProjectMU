// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUHUDWidget.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Attribute/MUStaminaAttributeSet.h"
#include "UI/MUHpWidget.h"
#include "UI/MUTimeGaugeWidget.h"

void UMUHUDWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUStaminaAttributeSet::GetCurrentStaminaAttribute()).AddUObject(this, &UMUHUDWidget::OnStaminaChanged);

		const UMUStaminaAttributeSet* CurrentAttributeSet = ASC->GetSet<UMUStaminaAttributeSet>();

		if (CurrentAttributeSet)
		{
			float CurrentStamina = CurrentAttributeSet->GetCurrentStamina();

			if (CurrentStamina > 0.f)
			{
				OnStaminaChanged_BP(CurrentStamina);
			}
		}

		HPWidget->SetAbilitySystemComponent(InOwner);
		TimeGaugeWidget->SetAbilitySystemComponent(InOwner);
	}
}

void UMUHUDWidget::OnStaminaChanged(const FOnAttributeChangeData& ChangeData)
{
	OnStaminaChanged_BP(ChangeData.NewValue);
}
