// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MUEnforcementManageComponent.h"
#include "Components/TextBlock.h"
#include "Library/MUFunctionLibrary.h"
#include "Singleton/MUEnforcementSubsystem.h"

void UMUEnforcementSelectionWidget::InitializeValue(EEnforcementType InEnforcementType,
                                                    FMUEnforcementSelection& InEnforcementData)
{
	EnforcementType = InEnforcementType;
	EnforcementData = InEnforcementData;

	SetupWidget();
	
	if ( IsValid( SelectionButton ) == true )
	{
		SelectionButton->OnClicked.AddDynamic( this, &UMUEnforcementSelectionWidget::OnSelectedButton );
	}
}

void UMUEnforcementSelectionWidget::OnSelectedButton()
{
	UMUEnforcementManageComponent* EnforcementManageComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );
	
	if (IsValid(EnforcementManageComponent) == true )
	{
		switch (EnforcementType)
		{
		case EEnforcementType::Attribute :
		case EEnforcementType::SkillEnforcement :
			{
				EnforcementManageComponent->EnforceAttributeAdded( EnforcementData.CharacterID, EnforcementData.EnforcementName, EnforcementData.EnforcementID);
				break;
			}
		case EEnforcementType::SkillOpen :
			{
				EnforcementManageComponent->EnforceSkillAdded( EnforcementData.CharacterID, EnforcementData.EnforcementSlot, EnforcementData.EnforcementID);
				break;
			}
		default:
			break;
		}
	}
	
	if ( OnEnforcementSelected.IsBound() == true )
	{
		OnEnforcementSelected.Broadcast();
	}
}

void UMUEnforcementSelectionWidget::SetupWidget()
{
	if ( !IsValid(EnforcementTitleText ) || !IsValid(EnforcementDescriptionText) || !IsValid(EnforcementImage) )
	{
		return;
	}

	
	FMUEnforcementData TempEnforcementData;

	if ( UMUFunctionLibrary::GetEnforcementData(this, EnforcementData.EnforcementID, TempEnforcementData) == false )
	{
		return;
	}

	EnforcementImage->SetBrushFromTexture( TempEnforcementData.DescriptionIcon );
	EnforcementTitleText->SetText( TempEnforcementData.DescriptionText );
	EnforcementDescriptionText->SetText( TempEnforcementData.DescriptionDetailText );
}
