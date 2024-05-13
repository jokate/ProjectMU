// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "Interface/InteractableTarget.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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
