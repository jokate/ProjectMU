// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_LowHp.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "체력 체크", Category = "MU")
class MOONU_API UEnvQueryTest_LowHp : public UEnvQueryTest
{
	GENERATED_BODY()

public :
	UEnvQueryTest_LowHp(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

#if UE_EDITOR
	virtual FText GetDescriptionTitle() const override;
#endif

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "체력이 낮은 경우 높은 점수"))
	bool bConsiderLowHp = false;
};
