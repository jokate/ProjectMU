// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeWindComponent.h"

#include "Interface/TimeWinder.h"


// Sets default values for this component's properties
UTimeWindComponent::UTimeWindComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsWinding = false;
}

void UTimeWindComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* GM = GetWorld()->GetAuthGameMode();

	if (GM == nullptr)
	{
		return;
	}

	const auto* Owner = GetOwner<ITimeWindTarget>();

	if (Owner == nullptr)
	{
		return;
	}

	auto* TGM = Cast<ITimeWinder>(GM);

	if (TGM)
	{
		TGM->RegisterTimeWindTarget(GetOwner());
	}
}

void UTimeWindComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	auto* GM = GetWorld()->GetAuthGameMode();

	if (GM)
	{
		const auto* Owner = GetOwner<ITimeWindTarget>();

		if (Owner)
		{
			if (auto* TGM = Cast<ITimeWinder>(GM))
			{
				TGM->UnregisterTimeWindTarget(GetOwner());
			}
		}
	}
	
	Super::EndPlay(EndPlayReason);
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

