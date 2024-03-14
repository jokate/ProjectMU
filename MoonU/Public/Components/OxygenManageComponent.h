// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/OxygenManager.h"
#include "OxygenManageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UOxygenManageComponent : public UActorComponent, public IOxygenManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOxygenManageComponent();

#pragma region IOxygenManager
	virtual void UseOxygen() override;
	
	virtual void RecoverOxygen() override;

	virtual void RecoverOxygen(const float InOxygen) override;

	virtual FOxygenUpdateDelegate& GetOxygenUpdateDelegate() override;
#pragma endregion
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnUseOxygen();
	
	UFUNCTION()
	void OnRecoverOxygen();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Oxygen | Max")
	float MaxOxygenAmount = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Oxygen | Current")
	float CurrentOxygenAmount;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer Interval")
	float TimerInterval = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen | Use Amount")
	float OxygenUseAmount = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Oxygen | Recover  Amount")
	float OxygenRecoverAmount = 0.5f;
	
	FTimerHandle OxygenTimerHandle;

	FTimerHandle RecoverTimerHandle;
	FOxygenUpdateDelegate OxygenUpdateDelegate;

};
