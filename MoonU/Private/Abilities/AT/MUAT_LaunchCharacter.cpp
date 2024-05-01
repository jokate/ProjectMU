// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_LaunchCharacter.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UMUAT_LaunchCharacter* UMUAT_LaunchCharacter::CreateTask(UGameplayAbility* InAbility, const FVector& DestinationVector)
{
	UMUAT_LaunchCharacter* Task = NewAbilityTask<UMUAT_LaunchCharacter>(InAbility);
	Task->DestVector = DestinationVector;

	return Task;
}

void UMUAT_LaunchCharacter::Activate()
{
	Super::Activate();
	
	ACharacter* Character = Cast<ACharacter>(Ability->GetAvatarActorFromActorInfo());

	if (Character == nullptr)
	{
		return;
	}
	
	FVector OutVector;
	
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, OutVector, Character->GetActorLocation(), DestVector);
	Character->LandedDelegate.AddDynamic(this, &UMUAT_LaunchCharacter::OnLanded);
	Character->LaunchCharacter(OutVector, true, true);

	SetWaitingOnAvatar();
}

void UMUAT_LaunchCharacter::OnDestroy(bool bInOwnerFinished)
{
	ACharacter* Character = Cast<ACharacter>(Ability->GetAvatarActorFromActorInfo());

	if (Character)
	{
		Character->LandedDelegate.RemoveDynamic(this, &UMUAT_LaunchCharacter::OnLanded);
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_LaunchCharacter::OnLanded(const FHitResult& HitResult)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnLaunchCompleted.Broadcast();
	}
}
