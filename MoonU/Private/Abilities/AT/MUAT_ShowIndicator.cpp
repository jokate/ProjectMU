// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_ShowIndicator.h"

#include "Components/DecalComponent.h"
#include "Framework/MUPlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void UMUAT_ShowIndicator::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	ShowIndicatorByIndicatorType();
}

void UMUAT_ShowIndicator::ShowIndicatorByIndicatorType()
{
	AActor* AvatarActor = GetAvatarActor();

	if ( IsValid(AvatarActor) == false )
	{
		return;
	}
	
	AMUPlayerController* PlayerController = AvatarActor->GetInstigatorController<AMUPlayerController>();

	if ( IsValid( PlayerController ) == false )
	{
		return;
	}

}

void UMUAT_ShowIndicator::Activate()
{
	Super::Activate();

	AActor* OwnerActor = GetAvatarActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OwnerActor);

	if ( IsValid( Character ) == false)
	{
		return;
	}	
	//SpawnedDecalComponent = UGameplayStatics::SpawnDecalAttached(IndicatorMaterial, FVector::ForwardVector, Character->GetMesh() );
}

void UMUAT_ShowIndicator::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}


