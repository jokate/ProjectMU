// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_TraceWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MUDefines.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AMUTA_TraceWeapon::AMUTA_TraceWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponSocketName = TEXT("Weapon_R_Trail_A");
}
