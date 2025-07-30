// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeWindComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"
#include "GameFramework/Character.h"	
#include "Interface/TimeWinder.h"


// Sets default values for this component's properties
UTimeWindComponent::UTimeWindComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsMaxRecordInit = false;
}

void UTimeWindComponent::BeginPlay()
{
	Super::BeginPlay();
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

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());

	if (AbilitySystemComponent)
	{
		for (const auto& RecordAttribute : RecordGameplayAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RecordAttribute).RemoveAll(this);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void UTimeWindComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (CachedASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMESTOP))
	{
		return;
	}
	
	if (CachedASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMEWINDING))
	{
		TimeRewind();
	}
	else
	{
		Record();
	}
}

FOnTimewindEnd& UTimeWindComponent::GetTimeWindEndEvent()
{
	return TimeWindEndEvent;
}

void UTimeWindComponent::OnInitialize()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}
	
	auto* GM = World->GetAuthGameMode();

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

	CachedASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());

	if (CachedASC)
	{
		for (const auto& RecordAttribute : RecordGameplayAttributes)
		{
			CachedASC->GetGameplayAttributeValueChangeDelegate(RecordAttribute).AddUObject(this, &UTimeWindComponent::OnChangedAttribute);
		}
	}
}

void UTimeWindComponent::TimeRewind()
{
	if (RecordDatas.Num() > 0)
	{
		const FTimeWindRecordData& RecordData = RecordDatas[0];
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
				CachedAnimInstance->Montage_Stop(0.0f);
			}
		}
		const TArray<FAttributeChangedRecord>& CurrentAttributeRecords = RecordData.AttributeChangedRecords;
		
		if (CurrentAttributeRecords.Num() > 0)
		{
			for (const auto& AttributeRecord : CurrentAttributeRecords)
			{
				CachedASC->SetNumericAttributeBase(AttributeRecord.Attribute, AttributeRecord.OldValue);
			}
		}
		
		RecordDatas.RemoveAt(0);
	}
	else
	{
		if (TimeWindEndEvent.IsBound())
		{
			TimeWindEndEvent.Broadcast();	
		}
	}
}

void UTimeWindComponent::Record()
{
	MaxRecord = FMath::RoundToInt32(RecordTime/ GetWorld()->GetDeltaSeconds());
	
	while (RecordDatas.Num() > MaxRecord)
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

	if (AttributeRecords.Num() > 0)
	{
		RecordData.AttributeChangedRecords = AttributeRecords;
		AttributeRecords.Empty();
	}
	
	RecordData.RewindVelocity = FVector(CachedCharacter->GetVelocity().X, CachedCharacter->GetVelocity().Y, 0); 
		
	RecordDatas.Insert(RecordData, 0);
}

void UTimeWindComponent::OnChangedAttribute(const FOnAttributeChangeData& Payload)
{
	if (CachedASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMEWINDING))
	{
		return;
	}
	
	FAttributeChangedRecord Record;
	Record.Attribute = Payload.Attribute;
	Record.OldValue = Payload.OldValue;

	AttributeRecords.Emplace(Record);
}

