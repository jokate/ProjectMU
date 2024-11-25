// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "MUCharacterBase.h"
#include "Data/MUEnum.h"
#include "Interface/Interactor.h"
#include "Interface/InventoryOwner.h"
#include "Interface/MUPlayer.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()

class MOONU_API AMUCharacterPlayer : public AMUCharacterBase, public IMUPlayer, public IInventoryOwner, public IInteractor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	const FVector2D GetRecentlyMovedVector();

	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f) override;

	void GASInputPressed(int32 InputId);

	void GASInputReleased(int32 InputId);

#pragma region Enforcement
	UFUNCTION()
	virtual void OnLevelUpCallbackFunction(int32 InLevel);
	
	UFUNCTION(BlueprintCallable)
	virtual void EnforcementUnit(int32 EnforcementID);
#pragma endregion

#pragma region Level p
#pragma endregion
	
protected :
	
	void SetupGASInputComponent();
	
#pragma region InputActionEvent
	void Move(const FInputActionValue& Value);

	void OnStopMove(const FInputActionValue& Value);
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
#pragma endregion

#pragma region IInventoryOwner
	virtual void AddItem(int32 ItemId, int32 ItemAmount) override;
	
	virtual void UseItemBySlot(int32 SlotIndex) override;
	virtual void UseItemByItemID(int32 ItemID) override;
#pragma endregion IInventoryOwner

#pragma region IInteractor
	virtual void TryInteract() override;

	virtual void SetCachedInteractionTarget(AActor* TargetActor) override;
#pragma endregion IInteractor

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory, meta = (AloowPrivateAccess = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInteractionComponent> InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enforcement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UEnforcementComponent> EnforcementComponent;

protected:
	UPROPERTY()
	FVector2D RecentlyMovedVector;
};