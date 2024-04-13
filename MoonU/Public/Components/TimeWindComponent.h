// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/TimeWinder/MUTimeWindData.h"
#include "Interface/TimerWindTarget.h"
#include "TimeWindComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UTimeWindComponent : public UActorComponent, public ITimeWindTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTimeWindComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void SetTimeWind(bool InTimeWind) override;
	virtual const bool GetTimeWind() override;

	void OnIntialize();
protected :
	void TimeRewind();
	
	void Record();

	void OnChangedAttribute(const FOnAttributeChangeData& Payload);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FTimeWindRecordData> RecordDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FAttributeChangedRecord> AttributeRecords;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGameplayAttribute> RecordGameplayAttributes;

	UPROPERTY(EditDefaultsOnly)
	float RecordTime = 3.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsWinding : 1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class ACharacter> CachedCharacter;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAnimInstance> CachedAnimInstance;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> CachedASC;

	UPROPERTY(VisibleAnywhere)
	int32 MaxRecord;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 bIsMaxRecordInit : 1;
};

