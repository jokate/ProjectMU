﻿// Fill out your copyright notice in the Description page of Project Settings.

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
enum EBlackboardKeyData
{
	BoolType,
	IntType,
	FloatType,
	VectorType,
	ActorType,
	ObjectType,
	EnumType
};

UENUM(BlueprintType)
enum EBTServiceActivationMode
{
	TickNode,
	BecomeRelevant,
	CeaseRelevant
};

UENUM(BlueprintType)
enum EAbilityActivationMode
{
	ByEvent,
	ByInputID,
};