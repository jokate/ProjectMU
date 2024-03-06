// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameInstance.h"

#include "Singleton/GameDataManager.h"

UMUGameInstance::UMUGameInstance()
{
	UMUGameSettings::Get();
}
