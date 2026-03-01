// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "StructUtils/InstancedStruct.h"
#include "MUAT_Trace.generated.h"

class AMUTA_Trace;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceResultDelegate, const FGameplayAbilityTargetDataHandle&,
                                            TargetDataHandle);
/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_Trace : public UAbilityTask
{
	GENERATED_BODY()

	UMUAT_Trace();
	
public :
	static UMUAT_Trace* CreateTask(UGameplayAbility* OwningAbility, const FName& TargetDamageInfo );

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	void SetupTraceData();

	AMUTA_Trace* SpawnAndInitializeTargetActor(TSubclassOf<AMUTA_Trace> TraceClass );

	void FinalizeTargetActor(AMUTA_Trace* TraceTarget, const FTransform& FinalizeTransform, const FName& AttachmentSocket = NAME_None);
protected:
	
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle);


public :

	UPROPERTY(BlueprintAssignable)
	FTraceResultDelegate OnComplete;
	
	UPROPERTY()
	TArray<AMUTA_Trace*> SpawnedTargetActors; 

	UPROPERTY()
	FName TargetDamageInfo;
};
