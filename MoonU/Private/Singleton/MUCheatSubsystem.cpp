// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/MUCheatSubsystem.h"

#include "Character/MUCharacterPlayer.h"


void UMUCheatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG( LogTemp, Log, TEXT("CheatSubsystem Initialized"));
}
