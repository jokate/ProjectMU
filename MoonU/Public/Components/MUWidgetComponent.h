// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MUWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUWidgetComponent();

public:
	virtual void InitWidget() override;
};
