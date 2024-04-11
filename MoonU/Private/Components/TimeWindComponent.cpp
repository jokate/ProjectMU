// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeWindComponent.h"


// Sets default values for this component's properties
UTimeWindComponent::UTimeWindComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsWinding = false;
}

void UTimeWindComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsWinding)
	{
		TimeRewind();
	}
	else
	{
		Record();		
	}
}

void UTimeWindComponent::SetTimeWind(bool InTimeRewind)
{
	bIsWinding = InTimeRewind;
}

const bool UTimeWindComponent::GetTimeWind()
{
	return bIsWinding;
}

void UTimeWindComponent::TimeRewind()
{
	if (RecordDatas.Num() > 0)
	{
		GetOwner()->SetActorLocation(RecordDatas[0].Position);
		GetOwner()->SetActorRotation(RecordDatas[0].Rotation);
		RecordDatas.RemoveAt(0);
	}
}

void UTimeWindComponent::Record()
{
	const int32 MaxRecord =  FMath::RoundToInt32(RecordTime / GetWorld()->DeltaTimeSeconds);
	if (RecordDatas.Num() > MaxRecord)
	{
		RecordDatas.RemoveAt(MaxRecord);
	}
	else
	{
		FTimeWindRecordData RecordData;
		RecordData.Position = GetOwner()->GetActorLocation();
		RecordData.Rotation = GetOwner()->GetActorRotation();
		RecordDatas.Insert(RecordData, 0);
	}
}

