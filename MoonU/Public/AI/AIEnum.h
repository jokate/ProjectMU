// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum ECharacterState
{
	None,
	Idle,
	Attack,
	Patrol,
};

UENUM(BlueprintType)
enum EDataToChange
{
	BOOLTYPE,
	INTTYPE,
	FLOATTYPE,
	VECTORTYPE
};