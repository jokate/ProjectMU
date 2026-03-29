// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/TimeWinder/MUTimeWindData.h"
#include "Interface/TimerWindTarget.h"
#include "MUCharacterRecordComponent.generated.h"

USTRUCT(BlueprintType)
struct FMUCharacterRecordPolicy
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Tags;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUCharacterRecordComponent : public UActorComponent, public ITimeWindTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUCharacterRecordComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual FOnTimewindEnd& GetTimeWindEndEvent() override;
	
	void OnInitialize();
	
protected :
	void Rewind();
	void Record();
	void Play();
	void OnChangedAttribute(const FOnAttributeChangeData& Payload);

	void PlayRecord(const FMUCharacterRecordData& CharacterRecordData);

	
	bool CheckPolicy(const FMUCharacterRecordPolicy& Policy) const;

public : 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FMUCharacterRecordData> RecordDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FAttributeChangedRecord> AttributeRecords;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGameplayAttribute> RecordGameplayAttributes;
	
	UPROPERTY(EditDefaultsOnly)
	FMUCharacterRecordPolicy RecordPolicy;

	UPROPERTY(EditDefaultsOnly)
	FMUCharacterRecordPolicy RewindPolicy;

	UPROPERTY(EditDefaultsOnly)
	FMUCharacterRecordPolicy PlayPolicy;
	
public : 
	UPROPERTY(EditDefaultsOnly)
	float RecordTime = 3.0f;

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
	

	FOnTimewindEnd TimeWindEndEvent;
};
