// Fill out your copyright notice in the Description page of Project Settings.

//Purpose : Blackboard로 Actor에 대해서 관리되는 것은 좋기는 하나, 세부적인 조건과 코드 레벨에서 확인하는 부분이 필요하기에 대한 컴포넌트를 사용하기로 한다.
//단, 해당 부분은 TargetLocation도 포함하기로 하자.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MUEnum.h"
#include "Interface/TargetManager.h"
#include "TargetManagingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UTargetManagingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetManagingComponent();

#pragma region Target Setter
	// Target에 대한 
	virtual bool IsTargetValid() const;
	
	virtual AActor* GetActorTarget() const { return TargetActor; }
	
	virtual void SetupTarget(AActor* NewTarget);

	virtual FVector GetTargetLocation() const { return TargetLocation; }
	
	virtual void SetupTargetLocation(FVector NewTargetLocation);

	virtual void ResetTarget();
#pragma endregion
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	UPROPERTY()
	FVector TargetLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActivationMode")
	TEnumAsByte<ETargetActivationType> ActivationType;
	
};
