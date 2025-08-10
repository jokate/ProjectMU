// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MUSkillTreeWidget.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS()
class MOONU_API UMUSkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY( BlueprintReadOnly )
	TObjectPtr<UOverlay> MainOverlay;

	//UPROPERTY()
};
