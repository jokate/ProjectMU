// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_AddLooseTag.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAnimNotifyState_AddLooseTag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	if (Owner == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);

	if (ASC == nullptr)
	{
		return;
	}

	ASC->AddLooseGameplayTag(NeedToAddTag);
}

void UAnimNotifyState_AddLooseTag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();

	if (Owner == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);

	if (ASC == nullptr)
	{
		return;
	}

	ASC->RemoveLooseGameplayTag(NeedToAddTag);
	
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
