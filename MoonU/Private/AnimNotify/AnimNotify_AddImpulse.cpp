// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_AddImpulse.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimNotify_AddImpulse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());

	if ( IsValid(Character) == false )
	{
		return;
	}

	UCharacterMovementComponent* CharacterMove = Character->GetCharacterMovement();

	if ( IsValid(CharacterMove) == false )
	{
		return;
	}

	CharacterMove->AddImpulse(ImpulseVector, bVelocityChange);
}


