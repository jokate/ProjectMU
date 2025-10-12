// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Data/MUEnum.h"
#include "Data/DataTable/MUData.h"
#include "MUInputConsumeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUInputConsumeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUInputConsumeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public :
	UFUNCTION()
	void ProcessConsumeInput();
	
	UFUNCTION(NetMulticast, Reliable)
	void MULTI_ConsumeInput(FGameplayTag ConsumeTag);
	virtual void MULTI_ConsumeInput_Implementation(FGameplayTag ConsumeTag);
	
	// Client Side에서 콤보처리.
	UFUNCTION(BlueprintCosmetic)
	void SendInput(ECombatInputType CombatInput);
	
public :
	UPROPERTY()
	TArray<FMUInputCommandList> AllInputCommandLists;
	
	// 타이머 돌리면서 인풋 관련 처리.

	TQueue<ECombatInputType> InputCombatQueue;

	UPROPERTY(EditDefaultsOnly)
	float InputConsumeTimeInterval = 0.2f;
	
	FTimerHandle InputConsumeTimer;
};
