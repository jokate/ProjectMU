// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VectorWrapper.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UVectorWrapper : public UObject
{
	GENERATED_BODY()

public :
	UVectorWrapper();
	
	void SetVector(const FVector& InVector);
	const FVector& GetVector() const;

protected :
	FVector WrappedVector;
};
