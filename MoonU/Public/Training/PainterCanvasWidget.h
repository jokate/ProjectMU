﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PainterCanvasWidget.generated.h"

class UCanvasRenderTarget2D;
class UButton;
class UCanvasWidget;
/**
 * 
 */
UCLASS()
class MOONU_API UPainterCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

public : 
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnPaintButtonPressed();
	
public :
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UCanvasWidget> CanvasWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> PaintButton;
};
