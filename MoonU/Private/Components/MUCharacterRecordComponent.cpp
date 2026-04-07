// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MUCharacterRecordComponent.h"
#include "GameFramework/GameModeBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"
#include "GameFramework/Character.h"	
#include "Interface/TimeWinder.h"


// Sets default values for this component's properties
UMUCharacterRecordComponent::UMUCharacterRecordComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsMaxRecordInit = false;
}

void UMUCharacterRecordComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMUCharacterRecordComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (IsValid(GM))
	{
		if (const ITimeWindTarget* Owner = GetOwner<ITimeWindTarget>())
		{
			if (auto* TGM = Cast<ITimeWinder>(GM))
			{
				TGM->UnregisterTimeWindTarget(GetOwner());
			}
		}
	}

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());

	if (IsValid(AbilitySystemComponent))
	{
		for (const auto& RecordAttribute : RecordGameplayAttributes)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RecordAttribute).RemoveAll(this);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void UMUCharacterRecordComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ( IsValid(CachedASC) == false )
	{
		return;
	}
	
	if (CachedASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMESTOP))
	{
		return;
	}
	
	if (CheckPolicy(RewindPolicy))
	{
		Rewind();
	}
	else if ( CheckPolicy(PlayPolicy))
	{
		Play();
	}
	else if ( CheckPolicy(RecordPolicy) )
	{
		Record(DeltaTime);
	}
}

FOnTimewindEnd& UMUCharacterRecordComponent::GetTimeWindEndEvent()
{
	return TimeWindEndEvent;
}

void UMUCharacterRecordComponent::OnInitialize()
{
	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		return;
	}
	
	AGameModeBase* GM = World->GetAuthGameMode();
	AActor* OwnerActor = GetOwner();
	if (IsValid(GM) == false || IsValid(OwnerActor) == false)
	{
		return;
	}

	if ( ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(OwnerActor))
	{
		if (ITimeWinder* TGM = Cast<ITimeWinder>(GM))
		{
			TGM->RegisterTimeWindTarget(GetOwner());
		}
	}
	
	if (ACharacter* Character = Cast<ACharacter>(OwnerActor))
	{
		CachedCharacter = Character;
	}

	USkeletalMeshComponent* Skel = OwnerActor->GetComponentByClass<USkeletalMeshComponent>();
	if ( IsValid(Skel) )
	{
		CachedAnimInstance = Skel->GetAnimInstance();
	}
	
	CachedASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor);

	if (CachedASC)
	{
		for (const auto& RecordAttribute : RecordGameplayAttributes)
		{
			CachedASC->GetGameplayAttributeValueChangeDelegate(RecordAttribute).AddUObject(this, &UMUCharacterRecordComponent::OnChangedAttribute);
		}
	}
}

void UMUCharacterRecordComponent::Rewind()
{
	if (RecordDatas.Num() > 0)
	{
		const FMUCharacterRecordData& RecordData = RecordDatas[0];
		PlayRecord(RecordData, RewindPolicy.bUseVelocity);
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

void UMUCharacterRecordComponent::Record(float DeltaTime)
{
	MaxRecord = FMath::RoundToInt32(RecordTime/ GetWorld()->GetDeltaSeconds());
	
	while (RecordDatas.Num() > MaxRecord)
	{
		RecordDatas.RemoveAt(MaxRecord);
	}
	
	FMUCharacterRecordData RecordData;
	RecordData.Position = GetOwner()->GetActorLocation();
	RecordData.Rotation = GetOwner()->GetActorRotation();

	//몽타주에 대해서 레코딩을 진행한다.
	if (IsValid(CachedAnimInstance))
	{
		if (UAnimMontage* CurrentMontage = CachedAnimInstance->GetCurrentActiveMontage())
		{
			const float CurrentPosition = CachedAnimInstance->Montage_GetPosition(CurrentMontage);

			FMUCharacterMontageRecordData MontageRecordData;
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

	RecordData.DeltaTime = DeltaTime;
	RecordDatas.Insert(RecordData, 0);
}

void UMUCharacterRecordComponent::Play()
{
	if (RecordDatas.Num() > 0)
	{
		const FMUCharacterRecordData& RecordData = RecordDatas.Pop();
		PlayRecord(RecordData, PlayPolicy.bUseVelocity);
	}
}

void UMUCharacterRecordComponent::PlayRecord(const FMUCharacterRecordData& CharacterRecordData, bool bUseVelocity)
{
	if ( bUseVelocity == false )
	{
		GetOwner()->SetActorLocation(CharacterRecordData.Position);
	}
	else
	{
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + CharacterRecordData.RewindVelocity * CharacterRecordData.DeltaTime);
	}

	GetOwner()->SetActorRotation(CharacterRecordData.Rotation);

	if (CharacterRecordData.MontageRecordData.Montage.Get() && CachedAnimInstance)
	{
		const FMUCharacterMontageRecordData& RecordMontageData = CharacterRecordData.MontageRecordData;
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
	const TArray<FAttributeChangedRecord>& CurrentAttributeRecords = CharacterRecordData.AttributeChangedRecords;
		
	if (CurrentAttributeRecords.Num() > 0)
	{
		for (const auto& AttributeRecord : CurrentAttributeRecords)
		{
			CachedASC->SetNumericAttributeBase(AttributeRecord.Attribute, AttributeRecord.OldValue);
		}
	}
}

bool UMUCharacterRecordComponent::CheckPolicy(const FMUCharacterRecordPolicy& Policy) const
{
	if ( Policy.bForce )
		return true;
	
	if ( Policy.Tags.Num() == 0 )
		return false;
	
	if ( IsValid(CachedASC) == false)
	{
		return false;
	}

	return CachedASC->HasAnyMatchingGameplayTags(Policy.Tags);
}

void UMUCharacterRecordComponent::OnChangedAttribute(const FOnAttributeChangeData& Payload)
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


