// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MUMontageAssetData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMUDamageMontageData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	FString DamageName;
};

UCLASS()
class MOONU_API UMUMontageAssetData : public UDataAsset
{
	GENERATED_BODY()

public :
#if UE_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
	static UAnimMontage* GetMontageData(AActor* OwnerCharacter, const FString& MontageName);
	static UMUMontageAssetData* GetMontageAssetData(AActor* OwnerCharacter);
	static UAnimMontage* GetDamageMontageByDamage(AActor* OwnerCharacter, float ProcessDamage);
	
public :
	UPROPERTY(EditAnywhere, DisplayName = "몽타주 데이터")
	TMap<FString, UAnimMontage*> MontageAssetData;

	UPROPERTY(EditAnywhere, DisplayName = "데미지 몽타주 관련처리")
	TArray<FMUDamageMontageData> DamageMontageData;
	
};
