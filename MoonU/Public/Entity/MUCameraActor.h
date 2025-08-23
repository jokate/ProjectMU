// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MUCameraActor.generated.h"

UCLASS()
class MOONU_API AMUCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReserveLocationAndRotation( FVector& Location, FRotator& Rotation );

	UFUNCTION()
	virtual void ProcessInterpolation();

public :
	UPROPERTY(EditAnywhere)
	FVector ReservedLocation;

	UPROPERTY(EditAnywhere)
	FRotator ReservedRotation;

	UPROPERTY(EditAnywhere)
	float InterpolationSpeed = 5.0f;

	UPROPERTY(EditAnywhere)
	FTimerHandle ReserveTimer;
};
