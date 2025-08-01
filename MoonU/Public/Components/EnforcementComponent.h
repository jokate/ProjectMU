﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "Data/DataTable/MUData.h"
#include "Interface/SkillManager.h"
#include "EnforcementComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UEnforcementComponent : public UActorComponent, public ISkillManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnforcementComponent();
	
	virtual void EnforceUnit(int32 InEnforcementID);
	
	virtual TArray<int32>& GetEnforcementIDs() { return EnforcementIDs; }

	virtual void AddSkillSlot( ESkillSlotType SkillSlotType, FName SkillID ) override;

	virtual void RemoveSkillSlot( ESkillSlotType SkillSlotType ) override;

	virtual const FName GetSkillIDBySlot( ESkillSlotType SkillSlot ) override;

	virtual void SetupSkillInput( FName SkillID );
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
#pragma region Enforcement
	virtual void EnforcementAttribute(FMUAttributeValue& AttributeValue);

	virtual void OpenSkill( FName SkillID );
#pragma endregion

	virtual void CallSkillUpdatedEvent();

	// 스킬 캐스팅 관련
	UFUNCTION()
	virtual void TriggerInputSkill( ESkillSlotType SkillSlot );
	
	virtual void InitializePlayerController();
	virtual void CastSkill( FName SkillID );
	virtual void TriggerSkill( FName SkillID );
	virtual void CancelSkill();

public:
	UPROPERTY( EditAnywhere )
	FName ReadySkillID = NAME_None;

	UPROPERTY( VisibleAnywhere )
	APlayerController* PlayerController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enforcement ID")
	TArray<int32> EnforcementIDs;

		UPROPERTY( VisibleAnywhere )
	TMap<ESkillSlotType, FName> AllocatedSkillID;
};
