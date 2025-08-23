// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MUAnimInstance.h"
#include "Animation/BlendSpace.h"
#include "Animation/BlendSpace1D.h"
#include "Character/MUCharacterPlayer.h"

void FMUAnimInstanceProxyData::ActiveProxy(const TSoftObjectPtr<UBlendSpace>& InBlendSpaceType, FName TargetBlendSpace)
{
	bIsActive = false;
	BlendSpace1D = nullptr;
	BlendSpace = nullptr;
	TargetBlendSpaceProperty = NAME_None;
	BlendSpaceType = EBlendSpaceType::NONE;
}

void FMUAnimInstanceProxyData::ActiveProxy(const TSoftObjectPtr<UBlendSpace1D>& InBlendSpaceType,
                                           FName TargetBlendSpace)
{
	BlendSpace1D = InBlendSpaceType.LoadSynchronous();
	TargetBlendSpaceProperty = TargetBlendSpace;
	bIsActive = true;
	BlendSpaceType = EBlendSpaceType::OneDim;
}

void FMUAnimInstanceProxyData::DeactivateProxy()
{
	bIsActive = false;
	BlendSpace1D = nullptr;
	BlendSpace = nullptr;
	TargetBlendSpaceProperty = NAME_None;
	BlendSpaceType = EBlendSpaceType::NONE;
}

bool FMUAnimInstanceProxy::Evaluate(FPoseContext& Output)
{
	const UMUAnimInstance* TempInstance = Cast<UMUAnimInstance>(GetAnimInstanceObject());

	if ( IsValid( TempInstance ) == false )
	{
		return false;
	}

	EvaluateAnimation(Output);
	
	return true;
}


void UMUAnimInstance::SampleBlendSpace()
{
	// 할당되지 않은 경우 한해서는 제외.
	if ( IsProxyActive() == false ||
		(AnimInstanceProxyData.BlendSpace1D == nullptr && AnimInstanceProxyData.BlendSpace == nullptr))
	{
		return;
	}
	
	TArray<FBlendSampleData> Samples;
}
