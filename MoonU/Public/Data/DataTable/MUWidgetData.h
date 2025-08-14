// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/MUEnum.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "MUWidgetData.generated.h"


USTRUCT(BlueprintType)
struct FInteractionBoardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InteractionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractionText;
};

USTRUCT( BlueprintType )
struct FAttributeEnforcementSlotData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WidgetCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;
};

USTRUCT( BlueprintType )
struct FEnforcementWidgetData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ESkillSlotType> NeedToAllocateSkillSlot;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FAttributeEnforcementSlotData> EnforcementSlotDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> AttributeSlotHorizontal;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<UUserWidget> AttributeWidgetClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TSubclassOf<UUserWidget> SkillSlotWidgetClass;
};

USTRUCT( BlueprintType )
struct FTopMenuItem
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TopMenuText;
};

USTRUCT(BlueprintType)
struct FTopMenuData : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTopMenuItem> ItemNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ItemWidgetClass;
};

