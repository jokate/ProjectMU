// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUFunctionLibrary.h"

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

ACharacter* UMUFunctionLibrary::GetLocalPlayerCharacter(UObject* WorldObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldObject, 0);
}

UGameplayTagSubsystem* UMUFunctionLibrary::GetGameplaySubSystem(UObject* WorldObject)
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldObject);

	if (GameInstance == nullptr)
	{
		return nullptr;
	}

	return GameInstance->GetSubsystem<UGameplayTagSubsystem>();
}
