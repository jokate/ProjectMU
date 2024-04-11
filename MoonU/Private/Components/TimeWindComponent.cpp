// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeWindComponent.h"
#include "GameFramework/Character.h"	
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

	if (auto* Character = GetOwner<ACharacter>())
	{
		CachedCharacter = Character;

		auto* MeshComp = CachedCharacter->GetMesh();

		if (MeshComp)
		{
			auto* AnimInstance = MeshComp->GetAnimInstance();

			if (AnimInstance)
			{
				CachedAnimInstance = AnimInstance;
			}
		}
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
		const FTimeWindRecordData RecordData = RecordDatas[0];
		GetOwner()->SetActorLocation(RecordData.Position);
		GetOwner()->SetActorRotation(RecordData.Rotation);

		if (RecordData.MontageRecordData.Montage.Get() && CachedAnimInstance)
		{
			const FTimeWindMontageRecordData RecordMontageData = RecordData.MontageRecordData;
			if (!CachedAnimInstance->Montage_IsPlaying(RecordMontageData.Montage.Get()))
			{
				CachedAnimInstance->Montage_Play(RecordMontageData.Montage.Get(), 1.0f, EMontagePlayReturnType::MontageLength, RecordMontageData.MontagePosition);
			}
			CachedAnimInstance->Montage_SetPosition(RecordMontageData.Montage.Get(), RecordMontageData.MontagePosition);
		}
		else
		{
			if (CachedAnimInstance->GetCurrentActiveMontage())
			{
				CachedAnimInstance->Montage_Stop(0.25f);
			}
		}
		
		
		RecordDatas.RemoveAt(0);
	}
}

void UTimeWindComponent::Record()
{
	const int32 MaxRecord = FMath::RoundToInt32(RecordTime / GetWorld()->DeltaTimeSeconds);
	if (RecordDatas.Num() > MaxRecord)
	{
		RecordDatas.RemoveAt(MaxRecord);
	}
	
	FTimeWindRecordData RecordData;
	RecordData.Position = GetOwner()->GetActorLocation();
	RecordData.Rotation = GetOwner()->GetActorRotation();

	//몽타주에 대해서 레코딩을 진행한다.
	if (CachedAnimInstance)
	{
		if (UAnimMontage* CurrentMontage = CachedAnimInstance->GetCurrentActiveMontage())
		{
			const float CurrentPosition = CachedAnimInstance->Montage_GetPosition(CurrentMontage);

			FTimeWindMontageRecordData MontageRecordData;
			MontageRecordData.Montage = CurrentMontage;
			MontageRecordData.MontagePosition = CurrentPosition;

			RecordData.MontageRecordData = MontageRecordData;	
		}
	}

	RecordData.RewindVelocity = FVector(CachedCharacter->GetVelocity().X, CachedCharacter->GetVelocity().Y, 0); 
		
	RecordDatas.Insert(RecordData, 0);
}

