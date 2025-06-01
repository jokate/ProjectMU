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
	virtual void BeginPlay() override;
	virtual void InitializePlayerController();
	virtual void CastSkill( FName SkillID );
	virtual void ReadySkill( FName SkillID );
	virtual void OnInputPressed();
	virtual void TriggerSkill( FName SkillID );


public:
	UPROPERTY( EditAnywhere )
	FName ReadySkillID = NAME_None;

	UPROPERTY( VisibleAnywhere )
	APlayerController* PlayerController;
};


