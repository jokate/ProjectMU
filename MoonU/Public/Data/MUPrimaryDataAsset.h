// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MUDefines.h"
#include "MUEnum.h"
#include "Engine/DataAsset.h"
#include "UI/Enforcement/MUSkillSlotWidget.h"
#include "MUPrimaryDataAsset.generated.h"

class UMUEnforcementSelectionCanvas;
class UMUEnforcementSelectionWidget;
class UEnforcementHorizontalWidget;
class UMUAttributeEnforceWidget;
/**
 * 
 */
UCLASS()
class MOONU_API UMUPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly )
	TMap< int32, FName > CharacterAttributeRegistry;

	UPROPERTY( EditDefaultsOnly )
	TMap<int32, FName > CharacterSkillRegistry;

	UPROPERTY( EditDefaultsOnly )
	TMap<ESkillSlotType, FGameplayTag> SkillInputTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEnforcementHorizontalWidget> AttributeSlotHorizontal;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<UMUAttributeEnforceWidget> AttributeWidgetClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<UMUSkillSlotWidget> SkillSlotWidgetClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMUEnforcementSelectionWidget> SelectionClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<UMUEnforcementSelectionCanvas> EnforcementSelectionCanvasClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	int32 SelectionMaximumCount = 3;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId( MU_ENFORCE_PRIMARY, GetFName());
	};
};
