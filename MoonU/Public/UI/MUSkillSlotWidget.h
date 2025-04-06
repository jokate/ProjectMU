// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MUEnum.h"
#include "MUSkillSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION( BlueprintCallable )
	void AllocateSkillID( FName SkillID );

	UFUNCTION( BlueprintPure )
	bool GetSkillIDForSlot(FName& SkillID) const;
	
public :
	UPROPERTY( EditAnywhere )
	ESkillSlotType SkillSlotType;
};
