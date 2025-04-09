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

UMUAT_ShowIndicator* UMUAT_ShowIndicator::CreateTask(UGameplayAbility* Ability, UMaterialInterface* SkillMaterial, float SkillDistance )
{
	UMUAT_ShowIndicator* IndicatorTask = NewAbilityTask<UMUAT_ShowIndicator>(Ability);

	IndicatorTask->IndicatorMaterial = SkillMaterial;
	IndicatorTask->SkillDistance = SkillDistance;

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

	//해당 데칼은 붙어서 동작하는 경우.
	float MouseX, MouseY;
	if ( PlayerController->GetMousePosition(MouseX, MouseY) == true )
	{
		FVector WorldLocation, WorldDirection;
		if ( PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection) )
		{
			// 현재 캐릭터를 기준으로 해서 돌려줘야 한다. -> Line일 경우.
			FVector CharacterLocation = AvatarActor->GetActorLocation();
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, WorldLocation);
			
			LookAtRotation.Pitch = 0.f;
			LookAtRotation.Roll = 0.f;

			UE_LOG(LogTemp, Log, TEXT(""))
			
			SpawnedDecalComponent->SetWorldRotation(LookAtRotation);
		}
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
	SpawnedDecalComponent = UGameplayStatics::SpawnDecalAttached(IndicatorMaterial, FVector::ForwardVector, Character->GetMesh() );
}

void UMUAT_ShowIndicator::OnDestroy(bool bInOwnerFinished)
{
	SpawnedDecalComponent->DestroyComponent();
	SpawnedDecalComponent = nullptr;
	
	Super::OnDestroy(bInOwnerFinished);
}


