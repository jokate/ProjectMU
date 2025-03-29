// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MUEnum.h"
#include "SkillManageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSkillUpdated );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API USkillManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USkillManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	virtual void AddSkillSlot( ESkillSlotType SkillSlotType, FName SkillID );

	virtual void RemoveSkillSLot( ESkillSlotType SkillSlotType );

	const FName GetSkillIDBySlot( ESkillSlotType SkillSlot );
	
public :

	UPROPERTY( BlueprintAssignable, BlueprintReadWrite )
	FOnSkillUpdated	OnSkillUpdated;
	
public :
	UPROPERTY( VisibleAnywhere )
	TMap<ESkillSlotType, FName> AllocatedSkillID;
};
