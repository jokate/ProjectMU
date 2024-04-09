// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define SPRINT_SPEED 800.0f

#define WALK_SPEED 400.0f

#define HEAD_BONE_NAME TEXT("head")

#define SUIT_TAG TEXT("Gameplay.Interactable.Suit")
#define COMBO_MOTION_WARP TEXT("Combo")

#define MU_INPUT_SPRINT FGameplayTag::RequestGameplayTag(FName("InputTag.Sprint"))
#define MU_INPUT_JUMP FGameplayTag::RequestGameplayTag(FName("InputTag.Jump"))
#define MU_INPUT_MOVE FGameplayTag::RequestGameplayTag(FName("InputTag.Move"))
#define MU_INPUT_LOOK FGameplayTag::RequestGameplayTag(FName("InputTag.Look"))
#define MU_INPUT_INTERACT FGameplayTag::RequestGameplayTag(FName("InputTag.Interact"))
#define MU_INPUT_LMATTACK FGameplayTag::RequestGameplayTag(FName("InputTag.LeftAttack"))
#define MU_INPUT_DODGE  FGameplayTag::RequestGameplayTag(FName("InputTag.Avoidance"))
#define MU_INPUT_CHARGE  FGameplayTag::RequestGameplayTag(FName("InputTag.ChargeTag"))
#define MU_UI_HUD  FGameplayTag::RequestGameplayTag(FName("Gameplay.UI.HUD"))
#define MU_EVENT_BLOCKRECOVER  FGameplayTag::RequestGameplayTag(FName("Event.Block.RecoverStamina"))