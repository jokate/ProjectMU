// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Animation/MUMontageAssetData.h"

#include "Character/MUCharacterBase.h"
#include "Library/MUFunctionLibrary.h"

#if UE_EDITOR
#include "UObject/UnrealTypePrivate.h"
#endif

#if WITH_EDITOR
void UMUMontageAssetData::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	const FName MemberPropertyName =
		PropertyChangedEvent.MemberProperty
		? PropertyChangedEvent.MemberProperty->GetFName()
		: NAME_None;

	const FName PropertyName =
		PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	// 최상위로 수정된 멤버가 DamageMontageData 배열인지 확인
	if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(UMUMontageAssetData, DamageMontageData))
	{
		DamageMontageData.HeapSort([&](const FMUDamageMontageData& A, const FMUDamageMontageData& B)
		{
			if ( A.Damage < B.Damage )
			{
				return true;
			}

			return false;
		});
	}
}
#endif

UAnimMontage* UMUMontageAssetData::GetMontageData(AActor* OwnerCharacter, const FString& MontageName)
{
	UMUMontageAssetData* CharMontageAssetData = GetMontageAssetData(OwnerCharacter);
	if ( IsValid(CharMontageAssetData) == false )
	{
		return nullptr;
	}

	const TMap<FString, UAnimMontage*>& MontageData = CharMontageAssetData->MontageAssetData;

	if ( MontageData.Contains(MontageName) )
	{
		return MontageData[MontageName];
	}

	return nullptr;
}

UMUMontageAssetData* UMUMontageAssetData::GetMontageAssetData(AActor* OwnerCharacter)
{
	AMUCharacterBase* Character = Cast<AMUCharacterBase>(OwnerCharacter);
	if ( IsValid(Character) == false )
	{
		return nullptr;
	}

	int32 CharacterID = Character->GetCharacterID();

	FMUCharacterInfo CharacterInfo;
	if ( UMUFunctionLibrary::GetCharacterInfoData(Character, CharacterID, CharacterInfo) == false )
	{
		return nullptr;
	}

	return CharacterInfo.MontageAssetData;
}

UAnimMontage* UMUMontageAssetData::GetDamageMontageByDamage(AActor* OwnerCharacter, float ProcessDamage)
{
	UMUMontageAssetData* CharMontageAssetData = GetMontageAssetData(OwnerCharacter);
	if (!IsValid(CharMontageAssetData))
	{
		return nullptr;
	}

	const TArray<FMUDamageMontageData>& MontageDatas = CharMontageAssetData->DamageMontageData;

	FString MontageName;
	float PrevDamage = 0.f;

	for (const FMUDamageMontageData& MontageData : MontageDatas)
	{
		if (ProcessDamage >= PrevDamage && ProcessDamage < MontageData.Damage)
		{
			MontageName = MontageData.DamageName;
			break;
		}
		MontageName = MontageData.DamageName;
		PrevDamage = MontageData.Damage;
	}

	return GetMontageData(OwnerCharacter, MontageName);
}