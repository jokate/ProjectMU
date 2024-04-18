// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityInitComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UAbilityInitComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityInitComponent();
	
	virtual void InitAbilities();

	virtual void OnEndPlay();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> InfiniteGameplayEffects;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayAbility>> NeedToStartAbilities;
};
