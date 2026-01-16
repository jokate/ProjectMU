// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameplayTagContainer.h"
#include "Character/MUCharacterBase.h"
#include "Data/MUEnum.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
#include "Indicator/MUSkillIndicator.h"
#include "MUData.generated.h"

/**
 * 
 */

class UGameplayAbility;

USTRUCT( BlueprintType )
struct FMUAttributeValue
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FGameplayAttribute InitAttribute;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float InitializedValue = 0;
};

USTRUCT( BlueprintType )
struct FMUAttributeInitValues
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FMUAttributeValue> Attributes;
};

USTRUCT(BlueprintType)
struct FMUAbilityChainingData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EAbilityChainingType AbilityChainingType = EAbilityChainingType::NONE;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability",
		meta = (EditCondition = "AbilityChainingType==EAbilityChainingType::Ability", EditConditionHides))
	TObjectPtr<UGameplayAbility> ChainTargetAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability",
		meta = (EditCondition = "AbilityChainingType==EAbilityChainingType::Montage", EditConditionHides))
	TObjectPtr<UAnimMontage> MontageToPlay;
};

USTRUCT( BlueprintType )
struct FMUAbilityStepData
{
	GENERATED_BODY()

public :
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 AbilityStep = 0;

	// 인풋에 대한 체이닝이 필요한 경우 (차지 공격 중에 구른다는 가정, 그러면 구르고 쏜다 이런 식. 아니면 몽타주로 가던가.)
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<FGameplayTag, FMUAbilityChainingData> InputChainingAbility;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AActor> TargetToSpawnActor;
};

USTRUCT( BlueprintType )
struct FInputFunctionalType
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	ETriggerEvent TriggerEvent = ETriggerEvent::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	TEnumAsByte<EGASInputFunctionalType> GASFunctionalType = EGASInputFunctionalType::Invalid;
};

//절대로 중복되는 경우는 없어야 합니다.
USTRUCT(BlueprintType)
struct FTagByInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	FGameplayTag InputTag;

	// Deprecated ID 기반으로 동작하는 방식은 이제 없습니다.
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	int32 InputID = 0;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputAbility)
	TSubclassOf<class UGameplayAbility> InputAbility;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = InputSetter)
	TArray<FInputFunctionalType> InputFunctionalTypes;
};

USTRUCT( BlueprintType )
struct FMUSkillInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	ETriggerEvent TriggerEvent = ETriggerEvent::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	ETriggerEvent ReleaseEvent = ETriggerEvent::None;
};


USTRUCT(BlueprintType)
struct FMUInputMapper : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Identity)
	int32 CharacterID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputConfig> InputConfig;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TArray<FTagByInput> InputByTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Comment")
	FString DevComment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Priority")
	int32 Priority = 0;
};

USTRUCT(BlueprintType)
struct FMUCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Identity")
	int32 CharacterID = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<class UGameplayEffect>> InfiniteGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<class UGameplayAbility>> NeedToStartAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TArray<TSubclassOf<class UAttributeSet>> NeedToRegisterAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TMap<int32, FMUAttributeInitValues> AttributeValueByLevel;
};

USTRUCT( BlueprintType )
struct FMUEnforcementData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnforcementID")
	int32 EnforcementID = 0;

	// 정보에 대한 서술.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dev Comment")
	FString DevComment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enforcement Type")
	TEnumAsByte<EEnforcementType> EnforcementType = EEnforcementType::MAX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Enforcement",
		meta = (EditCondition = "EnforcementType == EEnforcementType::Attribute", EditConditionHides))
	FMUAttributeValue EnforcementAttributeValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Enforcement",
		meta = (EditCondition = "EnforcementType == EEnforcementType::SkillOpen", EditConditionHides))
	FName SkillID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Description")
	FText DescriptionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Description")
	FText DescriptionDetailText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Description")
	UTexture2D* DescriptionIcon;
};

USTRUCT( BlueprintType )
struct FMUEnforcementProbability
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EnforcementID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnforcementProbability = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Prerequisite")
	TArray<int32> PrerequisiteID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Prerequisite")
	TEnumAsByte<ECheckOperationType> CheckOperationType;
};

USTRUCT( BlueprintType )
struct FMUEnforcementDropSelect : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMUEnforcementProbability> EnforcementProbabilities;
};

USTRUCT( BlueprintType )
struct FMUSkillData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseIndicator = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bUseIndicator == true", EditConditionHides))
	TSubclassOf<AMUSkillIndicator> SkillIndicatorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bUseIndicator == true", EditConditionHides))
	FVector IndicatorCameraOffSet = FVector::Zero();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bUseIndicator == true", EditConditionHides))
	FRotator IndicatorCameraRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SkillGameplayTag;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ability To Register")              
	TSubclassOf<class UGameplayAbility> NeedToRegAbility;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Casting Range")
	float CastingRange = 0;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Casting AOE" )
	float CastingAOE = 0;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Apply SkillSlot" )
	ESkillSlotType ApplySlotType = ESkillSlotType::NONE;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Visual Info")
	TObjectPtr<UTexture2D> SkillIcon = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Input" )
	FMUSkillInput SkillInput;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Active")
	TSoftObjectPtr<UAnimMontage> ActiveSkillMontage = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Active")
	bool bUseMotionWarp = false;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Active")
	FName MotionWarpName = NAME_None;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Active")
	TEnumAsByte<EMotionWarpType> MotionWarpType = EMotionWarpType::NoneMotionWarp;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Montage | Ready")
	TSoftObjectPtr<UAnimMontage> ReadySkillMontage = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	bool bUseObjectPooling = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bUseObjectPooling == true", EditConditionHides))
	int32 MaxCount = 1;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "SkillType")
	ESkillType SkillType = ESkillType::None;

	// 1가지 고민중.. (스킬 인풋에 관한 Granting 처리를 위해서 어떻게 동작해야 할까? )
	// 예를 들어서 콤보 관련한 부분의 경우에는 1 / 2 / 3 이런 식 가능 기본 공격하다가 구르기하면 다른 돌진이 나간다던가... 그런게 있으면 야무치란 말이지.. )
	// 조금 생각을 해보면 말야 일반 공격 ( 4타 / 3타 후 구르기 같은 콤보를 따로 두고 싶다면, 몽타주 섹션에 대한 처리를 하던지 아니면, 다른 어빌리티를 작동시켜야 할 듯 함 -> 연계의 기능이라면 더더.. )
	// 또 예를 들면 구르기 중에 다른 인풋이 들어왔다고 하면, 다른 어빌리티 연계적으로 실행도 가능했으면 좋겠단 말이지..
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillStepData")
	FMUAbilityStepData AbilityStepData;
};
	
USTRUCT( BLueprintType )
struct FMULevelData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	TSoftObjectPtr<UWorld> RoomLevel;
};

USTRUCT( BlueprintType )
struct FMUStageInfo : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY( EditAnywhere )
	int32 StageLevel = 0;

	UPROPERTY( EditAnywhere )
	TArray<FName> StageIDs;

	UPROPERTY( EditAnywhere )
	int32 MaxStage = 0;
};

USTRUCT( BlueprintType )
struct FMUStageData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TSoftObjectPtr<UWorld> RoomLevel;
	
};

USTRUCT( BlueprintType )
struct FMUMonsterSpawnData
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<AMUCharacterBase> CharacterClass;

	UPROPERTY( EditDefaultsOnly )
	int32 SpawnCount = 0;

	UPROPERTY( EditDefaultsOnly )
	int32 CharacterID = 0;
};

USTRUCT( BlueprintType )
struct FMUMonsterSpawnList : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray<FMUMonsterSpawnData> SpawnDatas;
};

USTRUCT( BlueprintType )
struct FMUProjectileInfo : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly )
	int32 HitCount = 1;	

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float CapsuleRadius = 0.f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float CapsuleHalfHeight = 0.f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float ProjectileSpeed = 0.f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UGameplayEffect> HitEffect;
};


// Purpose : 강화 요소 중 다시 돌렸을 시 코스트 및 레벨을 가져올 수 있도록 설계가 필요함.
// 데이터 구성 관련한 부분이 어떠헤 되어야 할 지 고민임.
USTRUCT( BlueprintType )
struct FMUEnforcementRerollCost
{
	GENERATED_BODY()

	public :
	
	//UPROPERTY( BlueprintReadOnly )
};

USTRUCT( BlueprintType )
struct FMUAttackEntityData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class AMUAttackEntity> AttackEntityClass;

	UPROPERTY( EditDefaultsOnly )
	int32 MaxPoolingCount = 1;

	UPROPERTY( EditDefaultsOnly )
	float LifeSpan = 1.f;
};

USTRUCT( BlueprintType )
struct FMUInputCommandList : public FTableRowBase
{
	GENERATED_BODY()

public :
	bool operator==(const FMUInputCommandList& Other) const
	{
		return Other.TargetGameplayTag == TargetGameplayTag;
	}
	
	void ConsumeInput(ECombatInputType InputType );

	bool CanConsumeInput() const;

	bool CanProcessInput() const;

	void Reset()
	{
		ProcessIndex = 0;
		bCanConsume = true;
	}

public :
	// 태그 리스트에 이미 있는 경우.
	UPROPERTY( EditDefaultsOnly )
	TArray<ECombatInputType> InputTypes;

	// 리턴될 태그 트리거.
	UPROPERTY( EditDefaultsOnly )
	FGameplayTag TargetGameplayTag;

	UPROPERTY( EditDefaultsOnly )
	bool bExactlyMatch = false;

	// 런타임 인풋
	UPROPERTY()
	int32 ProcessIndex = 0;

	UPROPERTY()
	bool bCanConsume = true;
};