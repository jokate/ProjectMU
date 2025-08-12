// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUSkillTreeWidget.h"

#include "Components/TextBlock.h"
#include "Singleton/MUEnforcementSubsystem.h"

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

void UMUSkillTreeWidget::SetupCharacterID(int32 InCharacterID)
{
	CharacterID = InCharacterID;

	// 캐릭터 ID에 대한 파싱 과정 필요.
	// 스킬 트리에 따른 부분 수정 조치 필요.
	OnEnforcementUpdated();
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
