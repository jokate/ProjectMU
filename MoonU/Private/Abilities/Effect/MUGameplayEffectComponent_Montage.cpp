// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Effect/MUGameplayEffectComponent_Montage.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSetBase.h"
#include "GameFramework/Character.h"

void UMUGameplayEffectComponent_Montage::OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer,
                                                                 FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const
{
	Super::OnGameplayEffectApplied(ActiveGEContainer, GESpec, PredictionKey);

	UAbilitySystemComponent* ASC = ActiveGEContainer.Owner;

	if ( IsValid( ASC ) == false )
	{
		return;
	}

	if ( ASC->HasAnyMatchingGameplayTags(BlockTag) )
	{
		return;
	}
	
	ACharacter* OwnerActor = ASC->GetOwner<ACharacter>();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Play Montage"));
	
	OwnerActor->PlayAnimMontage( MontageToPlay );
}
