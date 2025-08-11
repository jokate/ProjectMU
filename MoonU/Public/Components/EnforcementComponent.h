// Fill out your copyright notice in the Description page of Project Settings.

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
	
	virtual void EnforceAttribute(int32 InEnforcementID);
	
	virtual void EnforceSkill( ESkillSlotType SkillSlot, int32 InEnforcementID);
	
	virtual TArray<int32>& GetEnforcementIDs() { return EnforcementIDs; }

	virtual void AddSkillSlot( ESkillSlotType SkillSlotType, FName SkillID ) override;

	virtual void RemoveSkillSlot( ESkillSlotType SkillSlotType ) override;

	virtual const FName GetSkillIDBySlot( ESkillSlotType SkillSlot ) override;

	virtual void SetupSkillInput( FName SkillID );

	// 스킬 캐스팅 관련
	UFUNCTION()
	virtual void TriggerInputSkill( ESkillSlotType SkillSlot ) override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
#pragma region Enforcement
	virtual void EnforcementAttribute(FMUAttributeValue& AttributeValue);

	virtual void OpenSkill( ESkillSlotType SkillSlot, FName SkillID );
#pragma endregion

	virtual void CallSkillUpdatedEvent();
	
	virtual void CastSkill( FName SkillID );
	virtual void TriggerSkill( FName SkillID );
	virtual void CancelSkill();

public:
	UPROPERTY( EditAnywhere )
	FName ReadySkillID = NAME_None;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enforcement ID")
	TArray<int32> EnforcementIDs;

		UPROPERTY( VisibleAnywhere )
	TMap<ESkillSlotType, FName> AllocatedSkillID;
};
