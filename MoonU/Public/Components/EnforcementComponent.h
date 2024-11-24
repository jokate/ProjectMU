// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "Data/DataTable/MUData.h"
#include "EnforcementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UEnforcementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnforcementComponent();
	
	virtual void EnforceUnit(int32 InEnforcementID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma region Enforcement
	virtual void EnforcementAttribute(FMUAttributeValue& AttributeValue);

	virtual void OpenSkill(FSkillInfoData& SkillInfoData );
#pragma endregion
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enforcement ID")
	TArray<int32> EnforcementIDs;
};
