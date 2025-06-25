// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "MotionWarpingComponent.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSetBase.h"
#include "Components/AbilityInitComponent.h"
#include "Components/EQSActivationComponent.h"
#include "Components/TimeStopComponent.h"
#include "Components/TimeWindComponent.h"
#include "Interface/MUPlayer.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMUCharacterNonPlayer::AMUCharacterNonPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TimeStopComponent = CreateDefaultSubobject<UTimeStopComponent>("TimeStopComponent");
}

void AMUCharacterNonPlayer::OnDead(const FGameplayEventData* Data)
{
	if ( EnemyDeath.IsBound() == true )
	{
		EnemyDeath.Broadcast( this );
	}
}


UAbilitySystemComponent* AMUCharacterNonPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMUCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMUCharacterNonPlayer::SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType,
	const float MotionWarpValue)
{
	ReleaseMotionWarp(InName);
	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController == nullptr)
	{
		return;
	}

	AActor* TargetActor = AIController->GetFocusActor();

	if (TargetActor == nullptr)
	{
		return;
	}
	
	const FVector ActorLocation = GetActorLocation();
	//임시적인 값 부여.
	const FVector ToTargetActor = TargetActor->GetActorLocation() - ActorLocation;
	const FVector DirVector = FVector(ToTargetActor.X, ToTargetActor.Y, 0).GetSafeNormal();
	const FVector TargetLoc = ActorLocation + DirVector * MotionWarpValue;
	
	const FRotator ComponentRot = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetActor->GetActorLocation());
	const FRotator ComponentRotChanged = FRotator(0, ComponentRot.Yaw, 0);

	switch (InMotionWarpType)
	{
	case EMotionWarpType::TranslationAndRotation:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName,  TargetLoc, ComponentRotChanged);
		break;
	case EMotionWarpType::RotationOnly:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName, FVector::ZeroVector, ComponentRotChanged);
		break;
	case EMotionWarpType::TranslationOnly:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName, TargetLoc, FRotator::ZeroRotator);
		break;
	}
}
