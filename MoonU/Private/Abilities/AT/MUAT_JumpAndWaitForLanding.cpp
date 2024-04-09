// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UMUAT_JumpAndWaitForLanding::UMUAT_JumpAndWaitForLanding()
{
}

UMUAT_JumpAndWaitForLanding* UMUAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UMUAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UMUAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UMUAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &UMUAT_JumpAndWaitForLanding::OnLandedCallback);
	Character->Jump();
	
	//언제 점프가 끝날지 모르기 때문에, Waiting 형태로 만들어 준다.
	SetWaitingOnAvatar();
}

void UMUAT_JumpAndWaitForLanding::OnDestroy(bool bInOwnerFinished)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &UMUAT_JumpAndWaitForLanding::OnLandedCallback);
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}
