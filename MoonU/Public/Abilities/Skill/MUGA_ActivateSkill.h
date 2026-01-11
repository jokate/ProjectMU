// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
#include "Data/DataTable/MUData.h"
#include "Interface/SkillActivateAbility.h"
#include "MUGA_ActivateSkill.generated.h"

struct FMUSkillData;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSkillStateChanged );

UCLASS()
class MOONU_API UMUGA_ActivateSkill : public UGameplayAbility, public ISkillActivateAbility
{
	GENERATED_BODY()

public :
	
	UMUGA_ActivateSkill();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual bool CanUseSkill();

	virtual void CastSkill();

	virtual void SkillTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );

	virtual void SkillUnTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );

	virtual void SetupAnimMontage();
	
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

#pragma region Skill State
	virtual void ActivateSkill() override;
	virtual void CancelSkill() override;
	virtual FTransform GetTargetTransform() override
	{
		FTransform Result;
		Result.SetLocation(TargetLocation);
		Result.SetRotation(TargetRotation.Quaternion());
		return Result;
	}
	
	virtual FName GetSkillID() override
	{
		return SkillID;
	};

	
	void SetMontageSection(FName MontageSectionName) override;
#pragma endregion

	virtual ESkillType GetSkillType() const override { return SkillData.SkillType; }
	
public :
	virtual void SetComboPressed() override { bIsComboPressed = true; }
	virtual bool IsComboPressed() const override { return bIsComboPressed; }
	virtual void ResetComboPressed() override { bIsComboPressed = false; }
public :
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GameplayCueTags;

	UPROPERTY( BlueprintAssignable )
	FOnSkillStateChanged OnSkillStateChanged;
	
	UPROPERTY( EditDefaultsOnly )
	FName SkillID = NAME_None;

	UPROPERTY()
	FMUSkillData SkillData;
	
	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	FRotator TargetRotation;

	UPROPERTY()
	bool bIsComboPressed = false;
};
