// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUSkillTreeWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Library/MUFunctionLibrary.h"
#include "Singleton/MUEnforcementSubsystem.h"
#include "UI/EnforcementHorizontalWidget.h"
#include "UI/MUSkillSlotWidget.h"

void UMUSkillTreeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();

	if ( IsValid( PC ) == false )
	{
		return;
	}

	UMUEnforcementSubsystem* EnforcementSubsystem = ULocalPlayer::GetSubsystem<UMUEnforcementSubsystem>(PC->GetLocalPlayer());

	if ( IsValid( EnforcementSubsystem ) == true )
	{
		EnforcementSubsystem->OnEnforcementUpdated.AddDynamic( this, &UMUSkillTreeWidget::OnEnforcementUpdated );
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

void UMUSkillTreeWidget::OnEnforcementUpdated()
{
	APlayerController* PC = GetOwningPlayer();

	if ( IsValid( PC ) == false )
	{
		return;
	}
	
	UMUEnforcementSubsystem* EnforcementSubsystem = ULocalPlayer::GetSubsystem<UMUEnforcementSubsystem>(PC->GetLocalPlayer());

	if ( IsValid( EnforcementSubsystem ) == true )
	{
		int32 CurrentCost = EnforcementSubsystem->GetLevelEnforcementCost( CharacterID );

		CurrentCostText->SetText(FText::FromString(FString::Printf(TEXT("Current Score : %d"), CurrentCost)));
	}
}

void UMUSkillTreeWidget::InitializeWidget()
{
	if ( !IsValid( SkillSlotVertical ) || !IsValid(AttributeSlotVertical))
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
		UMUSkillSlotWidget* SkillSlotWidget = CreateWidget<UMUSkillSlotWidget>(this, EnforcementWidgetData.SkillSlotWidgetClass);

		if ( IsValid(SkillSlotWidget) == false)
		{
			continue;		
		}
		
		SkillSlotVertical->AddChildToVerticalBox( SkillSlotWidget );
		SkillSlotWidget->InitializeSkillSlot( CharacterID, SkillSlot );
		SkillSlotWidget->SetPadding( 50.f );
	}

	for ( FAttributeEnforcementSlotData& AttributeData : EnforcementWidgetData.EnforcementSlotDatas )
	{
		UEnforcementHorizontalWidget* SkillTreeDepth = CreateWidget<UEnforcementHorizontalWidget>(this, EnforcementWidgetData.AttributeSlotHorizontal );

		if ( IsValid(SkillTreeDepth) == false )
		{
			continue;
		}
		
		AttributeSlotVertical->AddChildToVerticalBox( SkillTreeDepth );
		SkillTreeDepth->InitializeWidget( CharacterID, AttributeData, EnforcementWidgetData.AttributeWidgetClass);
		SkillTreeDepth->SetPadding( 50.f );
	}
}
