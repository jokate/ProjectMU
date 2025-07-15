// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUHpWidget.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSetBase.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

	SetupPercent();
}

void UMUHpWidget::OnHpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentHealth = ChangeData.NewValue;
	SetupPercent();
}

void UMUHpWidget::OnMaxHpChanged(const FOnAttributeChangeData& ChangeData)
{
	CurrentMaxHealth = ChangeData.NewValue;
	SetupPercent();
}

void UMUHpWidget::SetupPercent()
{
	if ( IsValid( PbHpBar ) == true )
	{
		PbHpBar->SetPercent( CurrentHealth / CurrentMaxHealth );
	}

	if ( IsValid( HpText ) == true )
	{
		FString HpString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHealth, CurrentMaxHealth);
		HpText->SetText( FText::FromString(HpString) );
	}
}
