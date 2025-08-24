// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MUObjectPoolingManager.generated.h"

// 대체적으로 스킬에 대한 인포 정보가 담길듯.

USTRUCT(BlueprintType)
struct FObjectPoolInfo
{
	GENERATED_BODY()

public :
	UPROPERTY()
	TArray<UObject*> PoolingObjects;

	UPROPERTY()
	int32 PoolingMaxCount = 1;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUObjectPoolingManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUObjectPoolingManager();

public :
	virtual void GetPoolingObject( FName InSkillName ); 
	
public :
	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FObjectPoolInfo> PoolingMap;
};
