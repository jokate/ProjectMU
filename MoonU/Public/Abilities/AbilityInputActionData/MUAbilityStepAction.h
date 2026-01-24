// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "MUAbilityStepAction.generated.h"

class UMUGA_ActivateSkill;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FMUAbilityStepActionData
{
	GENERATED_BODY()
	
public : 
	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/MoonU.MUStepActionBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> InstancedStructContainer;
};


USTRUCT(BlueprintType)
struct MOONU_API FMUStepActionBase
{
	GENERATED_BODY()
	
public :
	virtual ~FMUStepActionBase() = default;

	virtual void OnStepIncreased(UMUGA_ActivateSkill* SkillAbility);
};


USTRUCT(BlueprintType, DisplayName = "몽타주 섹션 점프")
struct MOONU_API FMUStepAction_JumpToMontage : public FMUStepActionBase
{
	GENERATED_BODY()
	
public :
	virtual void OnStepIncreased(UMUGA_ActivateSkill* SkillAbility) override;
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TargetToJumpMontageSection;
};

USTRUCT(BlueprintType, DisplayName = "입력 타이머 딜레이 설정")
struct MOONU_API FMUStepAction_SetTimer : public FMUStepActionBase
{
	GENERATED_BODY()

public : 
	virtual auto OnStepIncreased(UMUGA_ActivateSkill* SkillAbility) -> void override;
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "타이머 시간"))
	float TargetTime = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "타이머 종료 시, 스탭 올릴지 여부."))
	bool bNeedToIncreaseStepWhenEnd = false;
};