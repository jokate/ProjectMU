// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Data/MUEnum.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
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
	ETriggerEvent TriggerEvent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	TEnumAsByte<EGASInputFunctionalType> GASFunctionalType;
	
};
USTRUCT(BlueprintType)
struct FTagByInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSetter)
	int32 InputID = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = InputSetter)
	TArray<FInputFunctionalType> InputFunctionalTypes;
};

USTRUCT( BlueprintType )
struct FSkillInfoData
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = InputSetter )
	bool bNeedToSetInput = true;
	
	//스킬에 따른 동작.
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = InputSetter,
		meta = (EditCondition = "bNeedToSetInput == true", EditConditionHides))
	FTagByInput TagByInput;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Ability To Register")
	TSubclassOf<class UGameplayAbility> NeedToRegAbility;
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
	TEnumAsByte<EEnforcementType> EnforcementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Enforcement",
		meta = (EditCondition = "EnforcementType == EEnforcementType::Attribute", EditConditionHides))
	FMUAttributeValue EnforcementAttributeValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill Enforcement",
		meta = (EditCondition = "EnforcementType == EEnforcementType::SkillOpen", EditConditionHides))
	FSkillInfoData SkillInfoData;
};
