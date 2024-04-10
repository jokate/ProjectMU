// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_Trace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);
/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

	UMUAT_Trace();
	
public :
	static UMUAT_Trace* CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<class AMUTA_Trace> TargetActorClass);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SpawnAndInitializeTargetActor();

	void FinalizeTargetActor();
protected:
	
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);


public :
	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;
	
	UPROPERTY()
	TObjectPtr<class AMUTA_Trace> SpawnedTargetActor; 
	
	UPROPERTY()
	TSubclassOf<class AMUTA_Trace> TargetActorClass;
};
