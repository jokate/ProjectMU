// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_UseStamina.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSet.h"

void UAnimNotify_UseStamina::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,  const FAnimNotifyEventReference& Ref)
{
	Super::Notify(MeshComp, Animation, Ref);

	AActor* OwningActor = MeshComp->GetOwner();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwningActor);

	if (!ASC)
	{
		return;
	}

	const float CurrentStamina = ASC->GetNumericAttribute(UMUCharacterAttributeSet::GetCurrentStaminaAttribute());

	ASC->SetNumericAttributeBase(UMUCharacterAttributeSet::GetCurrentStaminaAttribute(), CurrentStamina - StaminaToUse);
}
