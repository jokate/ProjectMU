// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGameplayAbility.generated.h"

/**
 * Please override this class to use Ability.
 * 태그 시스템을 사용하고 싶지는 않음.
 * (사유 유지보수 어려움 + 우후죽순 생겨나는게 싫음)
 */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor ))
enum class EMUAbilityActiveType : uint8
{
	None = 0				UMETA(DisplayName = "아무때나 사용 가능"),
	SkillReady = 1 << 1		UMETA(DisplayName = "레디 모션 중에 사용 불가"),
	SkillCasting = 1 << 2	UMETA(DisplayName = "스킬 캐스팅 중에 사용 불가")
};

UCLASS()
class MOONU_API UMUGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public :
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability", meta = (BitMask, BitMaskEnum = "Script/MoonU.EMUAbilityActiveType"))
	uint8 ActiveConditionCheck;
};
