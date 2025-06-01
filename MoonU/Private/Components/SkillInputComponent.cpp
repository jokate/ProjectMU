// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkillInputComponent.h"

#include "Indicator/MUIndicatorManageSubsystem.h"
#include "Library/MUFunctionLibrary.h"


// Sets default values for this component's properties
USkillInputComponent::USkillInputComponent()
{
}

void USkillInputComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializePlayerController();
}

void USkillInputComponent::InitializePlayerController()
{
	AActor* OwningActor = GetOwner();
	
	if ( IsValid( OwningActor ) == false )
	{
		return;		
	}

	APlayerController* OwnerActorController = OwningActor->GetInstigatorController<APlayerController>();

	if ( IsValid( OwnerActorController ) == false )
	{
		return;
	}

	PlayerController = OwnerActorController;
}

void USkillInputComponent::CastSkill(FName SkillID)
{
	FMUSkillData SkillData;
    if ( UMUFunctionLibrary::GetSkillData( this, SkillID, SkillData ) == false )
    {
    	return;
    }

	if ( SkillData.bUseIndicator == true )
    {
    	ReadySkill( SkillID );
    	return;
    }

	TriggerSkill( SkillID );
}

void USkillInputComponent::ReadySkill(FName SkillID)
{
	if ( ReadySkillID == SkillID )
	{
		return;
	}
	
	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->DeactivateSkillIndicator( ReadySkillID );
		
		ReadySkillID = SkillID;
		
		Subsystem->ActivateSkillIndicator( ReadySkillID );
	}
}

void USkillInputComponent::OnInputPressed()
{
	if ( ReadySkillID != NAME_None )
	{
		if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->DeactivateSkillIndicator( ReadySkillID );
		}
		
		TriggerSkill( ReadySkillID );
	}
}

void USkillInputComponent::TriggerSkill(FName SkillID)
{
	// 실질적인 GAS 트리거.
}