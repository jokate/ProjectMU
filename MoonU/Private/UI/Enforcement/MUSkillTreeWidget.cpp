// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUSkillTreeWidget.h"

#include "Components/MUEnforcementManageComponent.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Data/MUPrimaryDataAsset.h"
#include "Library/MUFunctionLibrary.h"
#include "UI/Enforcement/EnforcementHorizontalWidget.h"
#include "UI/Enforcement/MUAttributeEnforceWidget.h"
#include "UI/Enforcement/MUSkillSlotWidget.h"

void UMUSkillTreeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMUEnforcementManageComponent* EnforcementManageComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );

	if ( IsValid( EnforcementManageComponent ) == true )
	{
		EnforcementManageComponent->OnEnforcementUpdated.AddDynamic( this, &UMUSkillTreeWidget::OnEnforcementUpdated );
	}
}

void UMUSkillTreeWidget::SetupCharacterID(FName InCharacterID)
{
	int32 PrevCharacterID = CharacterID;
	
	CharacterID = FCString::Atoi(*InCharacterID.ToString());

	// 캐릭터 ID에 대한 파싱 과정 필요.
	// 스킬 트리에 따른 부분 수정 조치 필요.
	if ( CharacterID != PrevCharacterID )
	{
		OnEnforcementUpdated();
		// 무분별한 위젯 제거 방지.
		InitializeWidget();	
	}
}

void UMUSkillTreeWidget::SetupCharacterID(int32 InCharacterID)
{
	int32 PrevCharacterID = CharacterID;
	CharacterID = InCharacterID;

	if ( CharacterID != PrevCharacterID )
	{
		OnEnforcementUpdated();
		// 무분별한 위젯 제거 방지.
		InitializeWidget();	
	}
}

void UMUSkillTreeWidget::OnEnforcementUpdated()
{
	UMUEnforcementManageComponent* EnforcementManageComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );

	if ( IsValid( EnforcementManageComponent ) == true )
	{
		int32 CurrentCost = EnforcementManageComponent->GetLevelEnforcementCost( CharacterID );

		CurrentCostText->SetText(FText::FromString(FString::Printf(TEXT("Current Score : %d"), CurrentCost)));
	}
}

void UMUSkillTreeWidget::InitializeWidget()
{
	TSoftObjectPtr<UMUPrimaryDataAsset> DAPath = UMUFunctionLibrary::GetGlobalPrimaryDataAsset(this);
	UMUPrimaryDataAsset* DA = DAPath.LoadSynchronous();
	if ( !IsValid( SkillSlotVertical ) || !IsValid(AttributeSlotVertical) || !IsValid(DA))
	{
		return;
	}

	// 이렇게 한다면 GC에 저촉되지 않을까 의심스럽기는 함.
	SkillSlotVertical->ClearChildren();
	AttributeSlotVertical->ClearChildren();
	
	FEnforcementWidgetData EnforcementWidgetData;
	if ( UMUFunctionLibrary::GetEnforcementWidgetData(this, CharacterID, EnforcementWidgetData) == false )
	{
		return;
	}

	for ( ESkillSlotType SkillSlot : EnforcementWidgetData.NeedToAllocateSkillSlot )
	{
		UMUSkillSlotWidget* SkillSlotWidget = CreateWidget<UMUSkillSlotWidget>(this, DA->SkillSlotWidgetClass);

		if ( IsValid(SkillSlotWidget) == false)
		{
			continue;		
		}
		
		SkillSlotVertical->AddChildToVerticalBox( SkillSlotWidget );
		SkillSlotWidget->InitializeSkillSlot( CharacterID, SkillSlot );
		SkillSlotWidget->SetPadding( 50.f );
		SkillSlotWidget->OnSkillSlotClicked.AddDynamic( this, &UMUSkillTreeWidget::SkillTreeClicked );
	}

	for ( FAttributeEnforcementSlotData& AttributeData : EnforcementWidgetData.EnforcementSlotDatas )
	{
		UEnforcementHorizontalWidget* SkillTreeDepth = CreateWidget<UEnforcementHorizontalWidget>(this, DA->AttributeSlotHorizontal );

		if ( IsValid(SkillTreeDepth) == false )
		{
			continue;
		}
		
		AttributeSlotVertical->AddChildToVerticalBox( SkillTreeDepth );
		SkillTreeDepth->InitializeWidget( CharacterID, AttributeData, DA->AttributeWidgetClass);
		SkillTreeDepth->OnMemberClicked.AddDynamic( this, &UMUSkillTreeWidget::AttributeTreeClicked );
	}
}

void UMUSkillTreeWidget::SkillTreeClicked(ESkillSlotType SlotType)
{
	if ( OnSkillTreeClicked.IsBound() == true )
	{
		OnSkillTreeClicked.Broadcast(SlotType);
	}
}

void UMUSkillTreeWidget::AttributeTreeClicked(FName SlotName)
{
	if (OnAttributeTreeClicked.IsBound() == true)
	{
		OnAttributeTreeClicked.Broadcast(SlotName);
	}
}
