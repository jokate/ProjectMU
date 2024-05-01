// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorWrapper.h"

UVectorWrapper::UVectorWrapper()
{
}

void UVectorWrapper::SetVector(const FVector& InVector)
{
	WrappedVector = InVector;
}

const FVector& UVectorWrapper::GetVector() const
{
	return WrappedVector;
}
