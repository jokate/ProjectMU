// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUHUDWidget.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "UI/MUHpWidget.h"

void UMUHUDWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSet::GetCurrentStaminaAttribute()).AddUObject(this, &UMUHUDWidget::OnStaminaChanged);

		const UMUCharacterAttributeSet* CurrentAttributeSet = ASC->GetSet<UMUCharacterAttributeSet>();

		if (CurrentAttributeSet)
		{
			float CurrentStamina = CurrentAttributeSet->GetCurrentStamina();

			if (CurrentStamina > 0.f)
			{
				OnStaminaChanged_BP(CurrentStamina);
			}
		}

		HPWidget->SetAbilitySystemComponent(InOwner);
	}
}

void UMUHUDWidget::OnStaminaChanged(const FOnAttributeChangeData& ChangeData)
{
	OnStaminaChanged_BP(ChangeData.NewValue);
}
