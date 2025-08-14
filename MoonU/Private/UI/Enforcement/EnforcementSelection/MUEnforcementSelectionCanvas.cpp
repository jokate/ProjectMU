// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionCanvas.h"

#include "Components/HorizontalBox.h"
#include "Data/MUPrimaryDataAsset.h"
#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionWidget.h"
#include "Library/MUFunctionLibrary.h"

void UMUEnforcementSelectionCanvas::SetCharacterID(FName InCharacterID)
{
	CharacterID = FCString::Atoi(*InCharacterID.ToString());
}

void UMUEnforcementSelectionCanvas::SetupAttribute(FName AttributeSlotName)
{
	EnforcementSlotName = AttributeSlotName;
	EnforcementType = EEnforcementType::Attribute;

	AddSelectionMember();
}

void UMUEnforcementSelectionCanvas::SetupSkillAttribute(ESkillSlotType InSkillSlot)
{	
	SkillSlotType = InSkillSlot;
	EnforcementType = EEnforcementType::SkillOpen;

	AddSelectionMember();
}

void UMUEnforcementSelectionCanvas::AddSelectionMember()
{
	EnforcementSelectionHorizontal->ClearChildren();
	UMUPrimaryDataAsset* DA	= UMUFunctionLibrary::GetGlobalPrimaryDataAsset(this);
	if ( IsValid(DA) == false)
	{
		return;
	}
	
	// 레벨 1 고정 일단은..
	TSet<int32> EnforcementMembers;
	if ( UMUFunctionLibrary::GetEnforcementDropTable( this, CharacterID, EnforcementType, 1, DA->SelectionMaximumCount,  EnforcementMembers ) == false )
	{
		return;
	}

	for ( int32 Enforcement : EnforcementMembers )
	{
		UMUEnforcementSelectionWidget* SelectionWidget = CreateWidget<UMUEnforcementSelectionWidget>(this, DA->SelectionClass );

		if ( IsValid(SelectionWidget) == false)
		{
			continue;
		}

		EnforcementSelectionHorizontal->AddChildToHorizontalBox( SelectionWidget);
		SelectionWidget->SetPadding( PaddingValue );

		FMUEnforcementSelection Selection;
		Selection.EnforcementName = EnforcementSlotName;
		Selection.EnforcementSlot = SkillSlotType;
		Selection.CharacterID = CharacterID;
		Selection.EnforcementID = Enforcement;
		
		SelectionWidget->InitializeValue(EnforcementType, Selection);
		SelectionWidget->OnEnforcementSelected.AddDynamic( this, &UMUEnforcementSelectionCanvas::OnEnforcementSelected );
	}

	SetVisibility(ESlateVisibility::Visible);
}

void UMUEnforcementSelectionCanvas::OnEnforcementSelected()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
