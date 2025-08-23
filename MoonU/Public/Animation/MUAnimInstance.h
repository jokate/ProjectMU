// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "Data/MUEnum.h"
#include "MUAnimInstance.generated.h"

class UBlendSpace;
class UBlendSpace1D;

USTRUCT()
struct FMUAnimInstanceProxyData
{
	GENERATED_BODY()

public :
	void ActiveProxy(const TSoftObjectPtr<UBlendSpace>& InBlendSpaceType, FName TargetBlendSpace );

	void ActiveProxy(const TSoftObjectPtr<UBlendSpace1D>& InBlendSpaceType, FName TargetBlendSpace );

	void DeactivateProxy();
	
public :
	UPROPERTY()
	bool bIsActive = false;

	UPROPERTY()
	EBlendSpaceType BlendSpaceType;
	
	UPROPERTY()
	TObjectPtr<UBlendSpace> BlendSpace;

	UPROPERTY()
	TObjectPtr<UBlendSpace1D> BlendSpace1D;

	UPROPERTY()
	FName TargetBlendSpaceProperty;
};

USTRUCT()
struct FMUAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

public :
	FMUAnimInstanceProxy() {}
	FMUAnimInstanceProxy( UAnimInstance* AnimInstance ) : FAnimInstanceProxy( AnimInstance ) {}

	virtual bool Evaluate(FPoseContext& Output) override;
};

UCLASS()
class MOONU_API UMUAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :
	void ActiveProxy( const TSoftObjectPtr<UBlendSpace>& BS, FName TargetBlendSpace )
	{
		AnimInstanceProxyData.ActiveProxy(BS, TargetBlendSpace);
	}

	void ActiveProxy( const TSoftObjectPtr<UBlendSpace1D>& BS, FName TargetBlendSpace )
	{
		AnimInstanceProxyData.ActiveProxy(BS, TargetBlendSpace);
	}
	
	virtual void DeactivateProxy()
	{
		AnimInstanceProxyData.DeactivateProxy();
	}
	virtual bool IsProxyActive()
	{
		return AnimInstanceProxyData.bIsActive;
	}

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return new FMUAnimInstanceProxy( this );
	}
	
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override
	{
		delete static_cast<FMUAnimInstanceProxy*>(AnimInstanceProxy);
	}

	virtual void SampleBlendSpace();
	
public :
	UPROPERTY()
	FMUAnimInstanceProxyData AnimInstanceProxyData;
};
