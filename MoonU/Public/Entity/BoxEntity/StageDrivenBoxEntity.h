// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataDrivenBoxActor.h"
#include "StageDrivenBoxEntity.generated.h"

UCLASS()
class MOONU_API AStageDrivenBoxEntity : public ADataDrivenBoxActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStageDrivenBoxEntity();

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void SettingUpInformation() override;

	UFUNCTION()
	virtual void OnActiveStage( FName StageName );

	UFUNCTION()
	virtual void OnClearStage( FName ClearedStage );

	virtual void OnBoxInBound() override;

public :
	UPROPERTY( EditAnywhere, BlueprintReadWrite)
	TArray<FDataDrivenBox> BoundaryBoxes;

	UPROPERTY( BlueprintReadWrite )
	TArray<class UBoxComponent*> BoundaryBoxComponents;
	
	UPROPERTY(EditAnywhere)
	FName StageID = NAME_None;
};
