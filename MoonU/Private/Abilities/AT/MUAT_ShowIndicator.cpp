// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_ShowIndicator.h"
#include "Framework/MUPlayerController.h"
#include "Indicator/MUSkillIndicator.h"

UMUAT_ShowIndicator::UMUAT_ShowIndicator()
{
	bTickingTask = true;
}

UMUAT_ShowIndicator* UMUAT_ShowIndicator::CreateTask(UGameplayAbility* Ability, float SkillDistance, TSubclassOf<AMUSkillIndicator> InSkillIndicatorClass )
{
	UMUAT_ShowIndicator* IndicatorTask = NewAbilityTask<UMUAT_ShowIndicator>(Ability);
	IndicatorTask->SkillDistance = SkillDistance;
	IndicatorTask->SkillIndicatorClass = InSkillIndicatorClass;
	
	return IndicatorTask;
}

void UMUAT_ShowIndicator::Activate()
{
	Super::Activate();

	AActor* OwnerActor = GetAvatarActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	AMUPlayerController* PlayerController = OwnerActor->GetInstigatorController<AMUPlayerController>();

	if ( IsValid( PlayerController ) == false )
	{
		return;
	}

	SpawnedSkillIndicator = GetWorld()->SpawnActorDeferred<AMUSkillIndicator>(SkillIndicatorClass, OwnerActor->GetActorTransform() );

	if ( IsValid(SpawnedSkillIndicator ) == true )
	{
		SpawnedSkillIndicator->SetupIndicatorInfo( PlayerController, SkillDistance );

		FAttachmentTransformRules AttachmentRule {
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			true
		};
		
		SpawnedSkillIndicator->AttachToActor( OwnerActor, AttachmentRule );
		SpawnedSkillIndicator->FinishSpawning(OwnerActor->GetActorTransform() );
	}
}

void UMUAT_ShowIndicator::OnDestroy(bool bInOwnerFinished)
{
	if ( IsValid( SpawnedSkillIndicator ) == true )
	{
		SpawnedSkillIndicator->Destroy();	
	}
	
	Super::OnDestroy(bInOwnerFinished);
}


