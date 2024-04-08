// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_LauchCharacter.h"

#include "Character/MUCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotify_LauchCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());

	if (!Character)
	{
		return;
	}

	Character->LaunchCharacter(Character->GetActorForwardVector() * 5.0f, true, false);
	
}
