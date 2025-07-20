// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Data/MUEnum.h"
#include "GameFramework/Character.h"
#include "Interface/Defender.h"
#include "Interface/LevelManager.h"
#include "Interface/MotionWarpTarget.h"
#include "Interface/TimerWindTarget.h"
#include "MUCharacterBase.generated.h"

UCLASS()
class MOONU_API AMUCharacterBase : public ACharacter,
	public ITimeWindTarget, public IAbilitySystemInterface, public IMotionWarpTarget,
	public IGameplayTagAssetInterface, public IDefender, public IGenericTeamAgentInterface,
	public ILevelManager
{
	GENERATED_BODY()

public:
	
	AMUCharacterBase( const FObjectInitializer& ObjectInitializer );

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	virtual void RemoveMovementTags( EMovementMode PrevTag );

	virtual void AddMovementTags( EMovementMode CurrentTag );
	
#pragma region IGameplayTaagAssetInterface
	
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
#pragma endregion

#pragma region IMotionWarpTarget
	virtual class UMotionWarpingComponent* GetMotionWarpComponent(); 
	
	virtual void SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue = 0.0f);

	virtual void ReleaseMotionWarp(const FName InName);
#pragma endregion

	int32 GetCharacterID() const { return CharacterID; }

	FORCEINLINE void SetCharacterID( int32 InCharacterID ) { CharacterID = InCharacterID; }
	
	virtual void LevelUp() override;
 	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;
	
#pragma region ITimeWindTarget
	virtual FOnTimewindEnd& GetTimeWindEndEvent() override;
#pragma endregion

#pragma region IDefender
	
	virtual const FVector GetDefendRange() override;

	virtual const FTransform GetDefendTransform() override;

	UFUNCTION(BlueprintImplementableEvent)
	const FTransform GetDefendTransform_BP();
	
#pragma endregion

#pragma region IGenericTeamAgentInterface
	
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	virtual FGenericTeamId GetGenericTeamId() const override;
	
#pragma endregion

#pragma region ILevelManager
	virtual void SetLevel(int32 InLevel) override;

	UFUNCTION()
	void OnLevelSetCallbackFunction( int32 InLevel );
	
#pragma endregion

	virtual void SetMotionWarpToCursorDirection(const FName TargetName, EMotionWarpType InMotionWarpType, const FVector& TargetLocation, const FRotator& TargetRotation) override;
	
protected :
	UPROPERTY()
	TObjectPtr<class UMUAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Perception Stimuli Component")
	TObjectPtr<class UAIPerceptionStimuliSourceComponent> StimuliSourceComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Motion Warping")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability Init Component")
	TObjectPtr<class UAbilityInitComponent> AbilityInitComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time Wind Component")
	TObjectPtr<class UTimeWindComponent> TimeWindComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Up Component")
	TObjectPtr<class UMULevelUpComponent> LevelUpComponent;

public :
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defend Extent")
	FVector DefendExtent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test Character ID")
	int32 CharacterID = 0;

	public :
	UPROPERTY( EditDefaultsOnly, Category = "MovementMode | Tag" )
	TMap<TEnumAsByte<EMovementMode>, FGameplayTagContainer> NeedToAddMovementTag;

	UPROPERTY( EditDefaultsOnly, Category = "MovementMode | Tag"  )
	TMap<TEnumAsByte<EMovementMode>, FGameplayTagContainer> NeedToRemoveMovementTag;
};
