// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/LevelManager.h"
#include "MULevelUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpEventCallback, int32, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetLevelEventCallback, int32, Level);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMULevelUpComponent : public UActorComponent, public ILevelManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMULevelUpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void OnCharacterInitialized();
	
	virtual void LevelUp() override;

	FORCEINLINE virtual int32 GetLevel() const { return Level; }  

	FORCEINLINE virtual void SetLevel(const int32 InLevel) override { Level = InLevel; }
	
public :
	UPROPERTY( BlueprintReadOnly, BlueprintAssignable)
	FOnLevelUpEventCallback OnLevelUpEventCallback;

	UPROPERTY( BlueprintReadOnly, BlueprintAssignable )
	FOnSetLevelEventCallback OnSetLevelEventCallback;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Level")
	int32 Level = 1;
};
