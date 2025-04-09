// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_IndicatorSkill.h"
#include "MUGA_TestIndicatorSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_TestIndicatorSkill : public UMUGA_IndicatorSkill
{
	GENERATED_BODY()

public :
	void ActivateSkill() override;
};
