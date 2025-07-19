// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_SetNoSimulatedPhysics.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUAT_SetNoSimulatedPhysics* UMUAT_SetNoSimulatedPhysics::CreateTask(UGameplayAbility* OwningAbility)
{
	UMUAT_SetNoSimulatedPhysics* NewTask = NewAbilityTask<UMUAT_SetNoSimulatedPhysics>(OwningAbility);
	return NewTask;
}

void UMUAT_SetNoSimulatedPhysics::Activate()
{
	Super::Activate();

	AActor* OwningActor = GetAvatarActor();

	if ( IsValid( OwningActor ) == false )
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OwningActor);

	if ( IsValid(Character) == false )
	{
		return;
	}

	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();

	if ( IsValid( MovementComp ) == true )
	{
		MovementComp->GravityScale = 0.f;

		FVector Velocity = MovementComp->Velocity;
		Velocity.Z = 0.f;
		MovementComp->Velocity = Velocity;
	}
}

void UMUAT_SetNoSimulatedPhysics::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	
	Super::Activate();

	AActor* OwningActor = GetAvatarActor();

	if ( IsValid( OwningActor ) == false )
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OwningActor);

	if ( IsValid(Character) == false )
	{
		return;
	}

	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();

	if ( IsValid( MovementComp ) == true )
	{
		MovementComp->GravityScale = 1.f;
	}
}
