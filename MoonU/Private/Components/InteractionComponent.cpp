// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Interface/InteractableTarget.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	IAbilitySystemInterface* ASI = GetOwner<IAbilitySystemInterface>();

	if (ASI)
	{
		UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

		if (ASC)
		{
			FGameplayAbilitySpec Spec(RelatedAbility);
			ASC->GiveAbilityAndActivateOnce(Spec);
		}
	}
}

void UInteractionComponent::TryInteract()
{
	if (CachedActor == nullptr)
	{
		return;
	}

	IInteractableTarget* InteractableTarget = Cast<IInteractableTarget>(CachedActor);

	if (InteractableTarget)
	{
		InteractableTarget->OnInteracted(GetOwner());
	}
}

void UInteractionComponent::SetCachedInteractionTarget(AActor* TargetActor)
{
	CachedActor = TargetActor;
}
