// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "InputAction.h"
#include "Data/MUEnum.h"
#include "GameFramework/Character.h"
#include "Interface/TimerWindTarget.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class MOONU_API AMUCharacterPlayer : public ACharacter, public IAbilitySystemInterface, public ITimeWindTarget
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

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual class UMUComboActionData* GetComboActionData() const;

	FORCEINLINE virtual class UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }

	const FVector2D GetRecentlyMovedVector();
	
	void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f);

	void ReleaseMotionWarp(const FName InName);

	
protected:
	
#pragma region ITimeWindTarget
	virtual void SetTimeWind(bool InTimeRewind) override;
	virtual const bool GetTimeWind() override;
#pragma endregion
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS")
	TObjectPtr<class UAbilityInitComponent> AbilityInitComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Warping")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time Winder")
	TObjectPtr<class UTimeWindComponent> TimeWindComponent;
protected:
	UPROPERTY()
	FVector2D RecentlyMovedVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Action Data")
	TObjectPtr<class UMUComboActionData> ComboActionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<class UInputConfig> InputConfig;
};
