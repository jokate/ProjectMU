// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameplayTagContainer.h"
#include "Data/MUEnum.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
#include "Indicator/MUSkillIndicator.h"
#include "MUData.generated.h"

/**
 * 
 */

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	int32 InputID = 0;

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
	FGameplayTag InputTag;
	
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
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

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
	UTexture2D* SkillIcon = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Input" )
	FMUSkillInput SkillInput;
};

