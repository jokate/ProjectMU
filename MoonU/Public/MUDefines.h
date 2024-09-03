// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define SPRINT_SPEED 800.0f
#define WALK_SPEED 400.0f

#define TIMESTOPDILATION 0.0f
#define ORIGINALTIME 1.0f

#define EMPTY_ID 0
#define EMPTY_AMOUNT 0 

#define HEAD_BONE_NAME TEXT("head")

#define SUIT_TAG TEXT("Gameplay.Interactable.Suit")
#define DASH_MOTION_WARP TEXT("Dash")
#define COMBO_MOTION_WARP TEXT("Combo")

#define MU_INPUT_SPRINT FGameplayTag::RequestGameplayTag(FName("InputTag.Sprint"))
#define MU_INPUT_JUMP FGameplayTag::RequestGameplayTag(FName("InputTag.Jump"))
#define MU_INPUT_MOVE FGameplayTag::RequestGameplayTag(FName("InputTag.Move"))
#define MU_INPUT_LOOK FGameplayTag::RequestGameplayTag(FName("InputTag.Look"))
#define MU_INPUT_DEFENSE FGameplayTag::RequestGameplayTag(FName("InputTag.Defense"))
#define MU_INPUT_INTERACT FGameplayTag::RequestGameplayTag(FName("InputTag.Interact"))
#define MU_INPUT_LMATTACK FGameplayTag::RequestGameplayTag(FName("InputTag.LeftAttack"))
#define MU_INPUT_DODGE  FGameplayTag::RequestGameplayTag(FName("InputTag.Avoidance"))
#define MU_INPUT_CHARGE  FGameplayTag::RequestGameplayTag(FName("InputTag.ChargeTag"))
#define MU_INPUT_PERFECTDODGE  FGameplayTag::RequestGameplayTag(FName("InputTag.PerfectDodgeAttack"))
#define MU_INPUT_TIMESTOP  FGameplayTag::RequestGameplayTag(FName("InputTag.TimeStop"))
#define MU_INPUT_TIMEREWIND FGameplayTag::RequestGameplayTag(FName("InputTag.TimeRewind"))
#define MU_INPUT_ITEMUSE_QUICK FGameplayTag::RequestGameplayTag(FName("InputTag.ItemUse"))
#define MU_UI_HUD  FGameplayTag::RequestGameplayTag(FName("Gameplay.UI.HUD"))
#define MU_EVENT_BLOCKRECOVER  FGameplayTag::RequestGameplayTag(FName("Event.Block.RecoverStamina"))
#define MU_EVENT_TRACEEND  FGameplayTag::RequestGameplayTag(FName("Event.TraceEnd"))
#define MU_EVENT_ONHIT FGameplayTag::RequestGameplayTag(FName("Event.Character.OnHit"))
#define MU_EVENT_HITCOMPLETE FGameplayTag::RequestGameplayTag(FName("Event.HitComplete"))
#define MU_EVENT_TIMEREWIND FGameplayTag::RequestGameplayTag(FName("Event.TimeRewind"))
#define MU_EVENT_TIMESTOP FGameplayTag::RequestGameplayTag(FName("Event.TimeStop"))
#define MU_EVENT_TIMESTOPEND FGameplayTag::RequestGameplayTag(FName("Event.TimeStopEnd"))
#define MU_EVENT_TIMEREWINDEND FGameplayTag::RequestGameplayTag(FName("Event.TimeRewindEnd"))
#define MU_EVENT_DROPITEM FGameplayTag::RequestGameplayTag(FName("Event.DropItem"))
#define MU_EVENT_DROP_EXP FGameplayTag::RequestGameplayTag(FName("Event.DropExperience"))

#define MU_EVENT_ATTACKFINISHED FGameplayTag::RequestGameplayTag(FName("Event.AttackFinished"))
#define MU_EVENT_ATTACKSTARTED FGameplayTag::RequestGameplayTag(FName("Event.AttackStarted"))

#define MU_COLLISION_ROLL TEXT("RollCollision")
#define MU_COLLISION_PAWN TEXT("Pawn")

#define MU_CHARACTERSTATE_DODGE FGameplayTag::RequestGameplayTag(FName("Character.State.Dodge"))
#define MU_CHARACTERSTATE_PERFECTDODGE FGameplayTag::RequestGameplayTag(FName("Character.State.PerfectDodge"))
#define MU_CHARACTERSTATE_PERFECTDODGE_COMPLETE FGameplayTag::RequestGameplayTag(FName("Character.State.PerfectDodge.Complete"))
#define MU_CHARACTERSTATE_DEAD FGameplayTag::RequestGameplayTag(FName("Character.State.Dead"))
#define MU_CHARACTERSTATE_SUPERARMOR FGameplayTag::RequestGameplayTag(FName("Character.State.SuperArmor"))
#define MU_EVENT_REGENERATED FGameplayTag::RequestGameplayTag(FName("Event.Regenerated"))

#define MU_CHARACTERSTATE_DEFENDING FGameplayTag::RequestGameplayTag(FName("Character.State.Defend"))
#define MU_CHARACTERSTATE_TIMEWINDING FGameplayTag::RequestGameplayTag(FName("Character.State.TimeWinding"))
#define MU_CHARACTERSTATE_TIMESTOP FGameplayTag::RequestGameplayTag(FName("Character.State.TimeStop"))
#define MU_CHARACTERSTATE_PARRY FGameplayTag::RequestGameplayTag(FName("Character.State.Parry"))

#define MU_ITEM_TAG_CONSUMABLE FGameplayTag::RequestGameplayTag(FName("Item.Type.Consumable"))
#define MU_ITEM_TAG_EQUIPPABLE FGameplayTag::RequestGameplayTag(FName("Item.Type.Equippable"))