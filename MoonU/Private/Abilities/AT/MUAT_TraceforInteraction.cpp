// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_TraceforInteraction.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/InteractableTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UMUAT_TraceforInteraction::UMUAT_TraceforInteraction()
{
	bTickingTask = true;
}

UMUAT_TraceforInteraction* UMUAT_TraceforInteraction::CreateTask(UGameplayAbility* InAbility, float InInteractionRadius,
	float InLineCastLength)
{
	UMUAT_TraceforInteraction* NewTask = NewAbilityTask<UMUAT_TraceforInteraction>(InAbility);
	NewTask->InteractionRadius = InInteractionRadius;
	NewTask->LineCastLength = InLineCastLength;
	return NewTask;
}


void UMUAT_TraceforInteraction::Activate()
{
	Super::Activate();
	CachedOwningCharacter = Cast<ACharacter>(Ability->GetAvatarActorFromActorInfo());
}

void UMUAT_TraceforInteraction::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (CachedOwningCharacter->IsLocallyControlled())
	{
		SphereTraceForInteraction();
	}

	if (InteractionCheckFinished.IsBound())
	{
		InteractionCheckFinished.Broadcast(CachedActor);	
	}
}

void UMUAT_TraceforInteraction::SphereTraceForInteraction()
{
	if (CachedOwningCharacter == nullptr)
	{
		return;
	}
	
	CachedActor = nullptr;
	
	//반경에 따른 탐색을 지정한다.
	const FVector StartPoint = CachedOwningCharacter->GetCharacterMovement()->GetActorFeetLocation();
	const FVector EndPoint = StartPoint + FVector::UpVector;
	TArray<FHitResult> OutHitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes
	{
		UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1)
	};
	
	UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		this,
		StartPoint,
		EndPoint,
		InteractionRadius
		, ObjectTypes
		, false
		, TArray<AActor*>()
		, EDrawDebugTrace::None
		, OutHitResult
		, true
		);
	
	if (OutHitResult.Num() == 0)
	{
		return;
	}

	FilterInteraction(OutHitResult);
}

void UMUAT_TraceforInteraction::FilterInteraction(const TArray<FHitResult>& InHitResult)
{
	// Line Cast를 통해서 조절을 해줘야 한다고 생각.
	AController* PController = CachedOwningCharacter->GetController();
	if (PController == nullptr)
	{
		return;
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(PController);
	if (PlayerController == nullptr)
	{
		return;
	}
	FVector StartLocation;
	FRotator Direction;
	CachedOwningCharacter->GetActorEyesViewPoint(StartLocation, Direction);
	FVector DirectionVector = UKismetMathLibrary::GetForwardVector(Direction);
	FVector EndLocation = StartLocation + DirectionVector * LineCastLength;
	
	FHitResult OutHitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes
	{
		UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1)
	};
	
	UKismetSystemLibrary::LineTraceSingleForObjects
	(
		this,
		StartLocation,
		EndLocation,
		ObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		OutHitResult,
		true
	);
	
	AActor* LineHitActor = OutHitResult.GetActor();
	if (LineHitActor == nullptr)
	{
		return;
	}
	
	for (const FHitResult& HitResult : InHitResult)
	{
		const AActor* HitActor = HitResult.GetActor();

		if (HitActor == nullptr)
		{
			continue;
		}
		
		if (LineHitActor != HitActor)
		{
			continue;
		}
		auto* InteractableTarget = Cast<IInteractableTarget>(LineHitActor);
		if (InteractableTarget == nullptr)
		{
			continue;
		}

		if (InteractableTarget->IsInteractable(CachedOwningCharacter))
		{
			CachedActor = LineHitActor;
			break;
		}
	}
}

