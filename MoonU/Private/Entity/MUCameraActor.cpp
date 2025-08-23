// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MUCameraActor.h"


// Sets default values
AMUCameraActor::AMUCameraActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMUCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMUCameraActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ReserveTimer);
}

// Called every frame
void AMUCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMUCameraActor::ReserveLocationAndRotation(FVector& Location, FRotator& Rotation)
{
	ReservedLocation = Location;
	ReservedRotation = Rotation;

	if ( ReserveTimer.IsValid() == false )
	{
		GetWorld()->GetTimerManager().SetTimer( ReserveTimer, this, &AMUCameraActor::ProcessInterpolation,
			GetWorld()->GetDeltaSeconds(), true );
	}
}

void AMUCameraActor::ProcessInterpolation()
{
	float DeltaSec = GetWorld()->GetDeltaSeconds();
	AActor* AttachedActor = GetAttachParentActor();

	if (IsValid(AttachedActor) == false )
	{
		return;
	}

	FTransform ParentTransform = AttachedActor->GetActorTransform();
	FVector CalLoc = ParentTransform.TransformPosition(ReservedLocation);
	FRotator CalRot = ParentTransform.TransformRotation(ReservedRotation.Quaternion()).Rotator();
	
	if ( GetActorLocation() != CalLoc || GetActorRotation() != CalRot )
	{
		FVector NewLoc = FMath::VInterpTo(GetActorLocation(), CalLoc, DeltaSec, InterpolationSpeed);
		FRotator NewRot = FMath::RInterpTo(GetActorRotation(), CalRot, DeltaSec, InterpolationSpeed);
		
		SetActorLocation(NewLoc);
		SetActorRotation(NewRot);
	}
}

