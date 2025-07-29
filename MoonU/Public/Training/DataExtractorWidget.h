// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataExtractorWidget.generated.h"

/**
 * 
 */
class UDataTable;
UCLASS()
class MOONU_API UDataExtractorWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Train Data | Extract")
	void OnExtractButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "Train Data | Add Index")
	void AddRowForTrainingInfo(UDataTable* InfoDataTable, FName InRowName, FString FileName);

public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY( BlueprintReadWrite )
	UMaterialInstanceDynamic* RenderMaterial;

	UPROPERTY( BlueprintReadWrite )
	UMaterialInstanceDynamic* DrawMaterial;
};
