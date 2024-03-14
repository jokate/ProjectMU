// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUFunctionLibrary.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

ACharacter* UMUFunctionLibrary::GetLocalPlayerCharacter(UObject* WorldObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldObject, 0);
}

FGameplayTag UMUFunctionLibrary::GetInteractableGameplayTag(UObject* InteractableTarget)
{
	auto* Target = Cast<IInteractableTarget>(InteractableTarget);

	if (Target == nullptr)
	{
		return FGameplayTag();
	}
	
	return Target->GetEntityTag();
}

