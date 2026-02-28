// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvTest/EnvQueryTest_LowHp.h"

#include "Abilities/MUAbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/KismetMathLibrary.h"

UEnvQueryTest_LowHp::UEnvQueryTest_LowHp(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
	Cost = EEnvTestCost::Type::Low;
}

void UEnvQueryTest_LowHp::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for ( FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It )
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		if ( IsValid(ItemActor) == false )
		{
			continue;
		}

		UMUAbilitySystemComponent* ASC = UMUAbilitySystemComponent::Get(ItemActor);
		if ( IsValid(ASC) == false )
		{
			continue;
		}

		const UMUCharacterAttributeSet* Attribute = Cast<UMUCharacterAttributeSet>(ASC->GetAttributeSet(UMUCharacterAttributeSet::StaticClass()));

		if ( IsValid(Attribute) == false )
		{
			continue;
		}

		float TargetValue = bConsiderLowHp ? UKismetMathLibrary::SafeDivide(1, Attribute->GetCurrentHp()) : Attribute->GetCurrentHp();
		It.SetScore(TestPurpose, FilterType, TargetValue, 0.f , FLT_MAX);
	}
}

#if UE_EDITOR
FText UEnvQueryTest_LowHp::GetDescriptionTitle() const
{
	return FText::FromString(FString::Printf(TEXT("체력 기준으로 %s"), bConsiderLowHp ? TEXT("낮은 체력 우선") : TEXT("높은 체력 우선")));
}
#endif
