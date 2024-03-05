// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDrivenBoxActor.h"
#include "BasementBoxActor.generated.h"

UCLASS()
class MOONU_API ABasementBoxActor : public ADataDrivenBoxActor
{
	GENERATED_BODY()

public:
	ABasementBoxActor();
	
	virtual void OnBoxInBound() override;

	virtual void OnBoxOutBound() override;


protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Basement Mesh")
	TObjectPtr<UStaticMeshComponent> BasementMeshComponent;
};
