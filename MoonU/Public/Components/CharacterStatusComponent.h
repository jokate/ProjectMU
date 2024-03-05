// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatusComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public :
	void OnSprint();

	void OnUnsprint();

private :

	UFUNCTION()
	void UseStamina();

	UFUNCTION()
	void RecoverStamina();

	void OnUpdateStamina();
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SprintStamina")
	float MaxStamina = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sprint Stamina")
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina Decrease")
	float StaminaDecreaseAmount = 1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina Decrease")
	float StaminaRecoverAmount = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer Interval")
	float Interval = 0.1f;
	
	FTimerHandle SprintTimer;

	FTimerHandle RecoverTimer;
};
