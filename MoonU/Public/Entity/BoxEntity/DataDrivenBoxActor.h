// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MUStruct.h"
#include "GameFramework/Actor.h"
#include "DataDrivenBoxActor.generated.h"

UCLASS()
class MOONU_API ADataDrivenBoxActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADataDrivenBoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void CharacterBoundCheckLoop();
	
	bool CheckCharacterInBound(const FDataDrivenBox& DrivenBox) const;

#pragma region BoxBound Event
	virtual void OnBoxInBound();
	
	virtual void OnBoxOutBound();
#pragma endregion
	
public:
	
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> CachedLocalPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interval")
	float TimerInterval = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Driven Box")
	TArray<FDataDrivenBox> DataDrivenBoxes; 
	
	FTimerHandle CheckTimerHandle;
};
