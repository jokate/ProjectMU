// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MUPlayerHUD.generated.h"

class UMUHUDWidget;

/**
 * 
 */
UCLASS()
class MOONU_API AMUPlayerHUD : public AHUD
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly, Category = "HUD Widget")
	TSubclassOf<UMUHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "HUD Widget Instance")
	TObjectPtr<UMUHUDWidget> HUDWidgetInstance;
};
