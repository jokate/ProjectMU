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
#include "Interface/SkillInputTarget.h"
#include "Interface/SkillManager.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()

class MOONU_API AMUCharacterPlayer : public AMUCharacterBase, public IMUPlayer,
									 public IInventoryOwner, public IInteractor, public ISkillManager, public ISkillInputTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterPlayer( const FObjectInitializer& ObjectInitializer );

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual void SetupInputByID( int32 InputID );

	virtual bool IsSkillActive();
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	const FVector2D GetRecentlyMovedVector();

	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f) override;
	
	void GASInputPressed(int32 InputId);

	void GASInputReleased(int32 InputId);

	virtual const int32 GetPlayerCharacterID() override { return GetCharacterID(); }

	virtual void RegisterLocalStage();


#pragma region Level
	UFUNCTION(BlueprintCallable)
	virtual void ResetContinuousEnforcementLevel();

	UFUNCTION(BlueprintPure)
	virtual int32 GetContinuousEnforcementLevel();

	virtual bool GetEnforcementIDs(TArray<int32>& OutEnforcementIDs);
#pragma endregion

	void SetupCanLook( bool bInCanLook );
	
protected :
	
	void SetupGASInputComponent( int32 InputID );

	void SetupDefaultInput(UInputComponent* PlayerInputComponent);

	void SetupSkillInput( int32 InputID );

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

#pragma region ISkillManager

	virtual void TriggerInputSkill(ESkillSlotType SkillSlot) override;
	
	virtual void AddSkillSlot( ESkillSlotType SkillSlotType, FName SkillID ) override;

	virtual void RemoveSkillSlot( ESkillSlotType SkillSlotType ) override;

	virtual const FName GetSkillIDBySlot( ESkillSlotType SkillSlot ) override;

#pragma endregion

#pragma region Enforcement

	void RegisterEnforcementEvent();

	UFUNCTION()
	void OnAttributeEnforcementAdded(int32 InCharacterID, int32 EnforcementID);

	UFUNCTION()
	void OnSkillEnforcementAdded(int32 InCharacterID, ESkillSlotType SkillSlotType, int32 EnforcementID);
	
#pragma endregion
	
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

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "World Partition" )
	TObjectPtr<class UWorldPartitionStreamingSourceComponent> StreamingComponent;

protected:
	UPROPERTY()
	FVector2D RecentlyMovedVector;
};