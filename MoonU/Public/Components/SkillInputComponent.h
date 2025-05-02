// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SkillInputTarget.h"
#include "SkillInputComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API USkillInputComponent : public UActorComponent, public ISkillInputTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USkillInputComponent();
	
public : 
	void TriggerSkill();
	void CancelSkill();
	virtual FOnSkillActivate& GetActivationSkillEvent() override { return ActivateSkillEvent; }
	virtual FOnSkillDeactivate& GetDeactivationSkillEvent() override { return DeactivateSkillEvent; } 

protected : 
	FOnSkillActivate ActivateSkillEvent;
	
	FOnSkillDeactivate DeactivateSkillEvent;
};


