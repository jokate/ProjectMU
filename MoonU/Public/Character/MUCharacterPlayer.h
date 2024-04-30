// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "MUCharacterBase.h"
#include "Data/MUEnum.h"
#include "Interface/MUPlayer.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class MOONU_API AMUCharacterPlayer : public AMUCharacterBase, public IMUPlayer
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void PostInitializeComponents() override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION()
	void OnTimelineProgressed(float Value);
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	const FVector2D GetRecentlyMovedVector();

	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f) override;
protected :
	
	void SetupGASInputComponent();

	void GASInputPressed(int32 InputId);

	void GASInputReleased(int32 InputId);
	
#pragma region InputActionEvent
	void Move(const FInputActionValue& Value);

	void OnStopMove(const FInputActionValue& Value);
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void TimeWindActivate(bool InActivationMode);
	
#pragma endregion

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:
	UPROPERTY()
	FVector2D RecentlyMovedVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<class UInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline Component")
	TObjectPtr<class UTimelineComponent> TimelineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline Curve")
	TObjectPtr<class UCurveFloat> CameraMovementCurve;
};
