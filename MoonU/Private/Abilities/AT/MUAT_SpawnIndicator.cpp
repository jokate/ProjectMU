// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_SpawnIndicator.h"

#include "Indicator/MUIndicatorManageSubsystem.h"

UMUAT_SpawnIndicator* UMUAT_SpawnIndicator::CreateTask(UGameplayAbility* OwningAbility, FName InSkillID)
{
	UMUAT_SpawnIndicator* Task = NewAbilityTask<UMUAT_SpawnIndicator>(OwningAbility);

	Task->SkillID = InSkillID;

	return Task;
}

void UMUAT_SpawnIndicator::Activate()
{
	Super::Activate();

	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;	
	}
	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}

	APlayerController* PC = OwnerPawn->GetController<APlayerController>();

	if ( IsValid( PC ) == false )
	{
		return;
	}

	UMUIndicatorManageSubsystem* IndicatorManageSubsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer());

	if ( IsValid( IndicatorManageSubsystem ) == true )
	{
		IndicatorManageSubsystem->ActivateSkillIndicator( SkillID );
	}
}

void UMUAT_SpawnIndicator::OnDestroy(bool bInOwnerFinished)
{
	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;	
	}
	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}

	APlayerController* PC = OwnerPawn->GetController<APlayerController>();

	if ( IsValid( PC ) == false )
	{
		return;
	}

	UMUIndicatorManageSubsystem* IndicatorManageSubsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer());

	if ( IsValid( IndicatorManageSubsystem ) == true )
	{
		IndicatorManageSubsystem->DeactivateSkillIndicator( SkillID );
	}
	Super::OnDestroy(bInOwnerFinished);
}
