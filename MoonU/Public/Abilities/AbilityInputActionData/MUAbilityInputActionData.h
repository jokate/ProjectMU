// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MUAbilityInputActionData.generated.h"

/**
 * 
 */
#define RETURN_FALSE_IF_INVALID(Obj) \
if (!IsValid(Obj))               \
{                                \
	return false;                \
}

class UGameplayAbility;
class UMUGA_ActivateSkill;

USTRUCT(BlueprintType)
struct FAbilityInputActionBase
{
	GENERATED_BODY()
	
public :
	virtual ~FAbilityInputActionBase() = default;
	
	virtual bool OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
	{
		return false;
	}
	
	virtual bool IsSatisfiedInput(const FGameplayTag& SkillInputTag);
public : 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "타겟으로 삼는 이벤트 태그"))
	FGameplayTagContainer InputTagContainer;
};

USTRUCT(BlueprintType, DisplayName="콤보 처리")
struct FAbilityInputAction_SetComboPressed : public FAbilityInputActionBase
{
	GENERATED_BODY()
	
	virtual bool OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility) override;
};

USTRUCT(BlueprintType, DisplayName="몽타주 재생.")
struct FAbilityInputAction_PlayMontage : public FAbilityInputActionBase
{
	GENERATED_BODY()
	
	virtual bool OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility) override;
	
public : 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "재생될 몽타주"))
	TObjectPtr<UAnimMontage> TargetToPlayMontage;
};

USTRUCT(BlueprintType, DisplayName="어빌리티 트리거.")
struct FAbilityInputAction_TriggerAbility : public FAbilityInputActionBase
{
	GENERATED_BODY()
	
	virtual bool OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility) override;
	
public : 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "타겟 어빌리티"))
	TSubclassOf<UGameplayAbility> AbilityClass;
};