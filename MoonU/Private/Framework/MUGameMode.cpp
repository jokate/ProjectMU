// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameMode.h"

#include "Components/TimeWindManager.h"

AMUGameMode::AMUGameMode()
{
	TimeWindManager = CreateDefaultSubobject<UTimeWindManager>("TimeWindManager");
}
