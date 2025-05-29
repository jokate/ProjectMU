// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUIndicatorManageSubsystem.h"

void UMUIndicatorManageSubsystem::RegisterIndicator(FName IndicatorID, AMUSkillIndicator* Indicator)
{
	if ( IndicatorManagement.Contains(IndicatorID) == false)
	{
		IndicatorManagement.Add(IndicatorID, Indicator);
	}
}

AMUSkillIndicator* UMUIndicatorManageSubsystem::GetIndicatorByType(FName IndicatorID)
{
	if ( HasIndicator(IndicatorID) == false)
	{
		return nullptr;		
	}

	return IndicatorManagement[IndicatorID];
}
