// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_ActivateSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Abilities/AbilityInputActionData/MUAbilityInputActionData.h"
#include "Abilities/AbilityInputActionData/MUAbilityStepAction.h"
#include "Abilities/AT/MUAT_SetTimerAndWait.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Interface/MotionWarpTarget.h"
#include "Library/MUFunctionLibrary.h"

UMUGA_ActivateSkill::UMUGA_ActivateSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UMUGA_ActivateSkill::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	FMUSkillData TempSkill;
	if ( UMUFunctionLibrary::GetSkillData(ActorInfo->AvatarActor.Get(), SkillID, TempSkill) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 없음!"));
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UMUGA_ActivateSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAbilitySystemComponent* ASC = Cast<UMUAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()));

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->ExecuteGameplayCue(GameplayCueTag);
		}

		ASC->AddActiveAbility(this);
	}
	
	UMUFunctionLibrary::GetSkillData(ActorInfo->AvatarActor.Get(), SkillID, SkillData);
	ProcessStep();
}

void UMUGA_ActivateSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	UMUAbilitySystemComponent* ASC = Cast<UMUAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get()));

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);
		}

		ASC->RemoveActiveAbility(this);
	}

	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(ActorInfo->OwnerActor.Get());
	
	if (MotionWarp != nullptr && SkillData.bUseMotionWarp )
	{
		MotionWarp->ReleaseMotionWarp(SkillData.MotionWarpName);
	}

	SkillStepCount = 0;
	bIsComboPressed = false;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UMUGA_ActivateSkill::CanUseSkill()
{
	if ( CheckCooldown(CurrentSpecHandle, CurrentActorInfo ) == false )
	{
		return false;
	}

	if ( CheckCooldown(CurrentSpecHandle, CurrentActorInfo ) == false )
	{
		return false;
	}

	return true;
}

void UMUGA_ActivateSkill::CastSkill()
{
	if ( CanUseSkill() == false )
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false );
	}
	else
	{
		ActivateSkill();
	}
}

void UMUGA_ActivateSkill::ActivateSkill()
{
	ApplyCost( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );
	ApplyCooldown( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );

	UAnimMontage* ActiveMontage = SkillData.ActiveSkillMontage.LoadSynchronous();

	if ( IsValid(ActiveMontage) == false )
	{
		return;
	}
	
	SetupAnimMontage(ActiveMontage);
	
	if ( OnSkillStateChanged.IsBound() == true )
	{
		OnSkillStateChanged.Broadcast();
	}
}

void UMUGA_ActivateSkill::CancelSkill()
{
	if ( OnSkillStateChanged.IsBound() == true )
	{
		OnSkillStateChanged.Broadcast();
	}
}

void UMUGA_ActivateSkill::SetMontageSection(FName MontageSectionName)
{
	MontageJumpToSection(MontageSectionName);
	bIsComboPressed = false;
	
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	
	if (IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor)  )
	{
		if ( SkillData.bUseMotionWarp ) 
			MotionWarp->SetMotionWarp(SkillData.MotionWarpName, SkillData.MotionWarpType);
	}
}

// 보통 콤보의 경우에는 특정 상황 중에 눌렀다 뗐따 눌렀다 뗐다 하지 않나..?
bool UMUGA_ActivateSkill::ReceivePressedTag(const FGameplayTag& InputTag)
{
	return ProcessInput(true, InputTag);
}

// 얘는 우얄까.. 조준 같은 경우에는 조준이 끝났다! 라는 사실을 알리기는 해야 함.. 차지 공격의 경우에는 차징중... 똭! 이렇게 들어가야 하고 말이지..
bool UMUGA_ActivateSkill::ReceiveReleasedTag(const FGameplayTag& InputTag)
{
	return ProcessInput(false, InputTag);
}

void UMUGA_ActivateSkill::OnStepTimeComplete(bool bNeedToIncrement)
{
	FMUAbilityStepData* StepData = SkillData.GetStepData(SkillStepCount);
	
	if ( StepData == nullptr )
	{
		return;
	}
	
	// 차지 공격의 한하여 다음과 같이 동작한다는 거군...
	if (bNeedToIncrement)
	{
		ProcessStep();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UMUGA_ActivateSkill::SetupAbilityStepTimer(float TargetTime, bool bNeedToIncreaseStepWhenEnded)
{
	// 딜레이 옵션 없으면 굳이 미실행.
	if ( TargetTime <= 0.f )
	{
		return;
	}
	
	UMUAT_SetTimerAndWait* TimerWait = UMUAT_SetTimerAndWait::CreateTask(this, TargetTime, bNeedToIncreaseStepWhenEnded);
	
	if ( IsValid(TimerWait) )
	{
		TimerWait->OnFinished.BindUObject(this, &UMUGA_ActivateSkill::OnStepTimeComplete);
		TimerWait->ReadyForActivation();
	}
}


void UMUGA_ActivateSkill::TriggerAbility(TSubclassOf<UGameplayAbility> AbilityClass)
{
	// 연계할 어빌리티를 트리거 한다.
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if ( IsValid(ASC) == true )
	{
		FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(AbilityClass);

		if ( AbilitySpec != nullptr && 	ASC->TryActivateAbility(AbilitySpec->Handle))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		}
	}
}

bool UMUGA_ActivateSkill::ProcessInput(bool bIsPressed, const FGameplayTag& InputTag)
{
	bool bIsProcessed = false;
	
	TMap<int32, FMUInputStepData>& Functor = bIsPressed ? InputPressedFunctor : InputReleasedFunctor;
	
	FMUInputStepData* StepData = Functor.Find(SkillStepCount);
	if ( StepData == nullptr )
	{
		return false;
	}
	
	for ( FInstancedStruct& PressFunctor : StepData->InstancedStructContainer)
	{
		FAbilityInputActionBase* AbilityInputActionBase = PressFunctor.GetMutablePtr<FAbilityInputActionBase>();
		
		if ( AbilityInputActionBase == nullptr )
		{
			continue;
		}
		
		if ( AbilityInputActionBase->IsSatisfiedInput(InputTag) )
		{
			bIsProcessed = AbilityInputActionBase->OnInputEventCallback(this);	
		}
	}
	
	return bIsProcessed;
}

void UMUGA_ActivateSkill::ProcessStep()
{
	++SkillStepCount;
	FMUAbilityStepActionData* StepData = AbilityStepActionData.Find(SkillStepCount);
	if ( StepData == nullptr )
	{
		return;
	}
	
	for ( FInstancedStruct& PressFunctor : StepData->InstancedStructContainer)
	{
		FMUStepActionBase* AbilityStepActionBase = PressFunctor.GetMutablePtr<FMUStepActionBase>();
		
		if ( AbilityStepActionBase == nullptr )
		{
			continue;
		}
		
		AbilityStepActionBase->OnStepIncreased(this);
	}
}

void UMUGA_ActivateSkill::SkillTriggered(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// 여부에 따라서 스킬 트리거가 바로 Ability를 실행 할 수도 혹은 실행된 상태에서만 동작할 수도 있음.  ( 테스트 필요함 )
}

void UMUGA_ActivateSkill::SkillUnTriggered(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	CancelSkill();
	EndAbility( Handle, ActorInfo, ActivationInfo, true, true );
}

void UMUGA_ActivateSkill::SetupAnimMontage(UAnimMontage* TargetToPlayMontage)
{
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	
	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor);
	
	if (MotionWarp == nullptr || IsValid(TargetToPlayMontage) == false )
	{
		return;
	}

	// 태스크 처리 되고 있는 부분을 리셋.
	if ( Task_PlayMontageAndWait.IsValid() ) 
	{
		Task_PlayMontageAndWait->EndTask();
		Task_PlayMontageAndWait = nullptr;
	}
	
	Task_PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, SkillID, TargetToPlayMontage,
		1.0f, NAME_None, true );
	
	Task_PlayMontageAndWait->OnCompleted.AddDynamic(this, &UMUGA_ActivateSkill::OnCompleteCallback);
	Task_PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);
	Task_PlayMontageAndWait->OnCancelled.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);
	Task_PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);

	if ( SkillData.bUseMotionWarp == true)
	{
		SkillData.bUseIndicator ?
			MotionWarp->SetMotionWarpToCursorDirection(SkillData.MotionWarpName,SkillData.MotionWarpType, TargetLocation, TargetRotation )
			: MotionWarp->SetMotionWarp(SkillData.MotionWarpName, SkillData.MotionWarpType);
	}
	
	Task_PlayMontageAndWait->ReadyForActivation();
}

void UMUGA_ActivateSkill::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_ActivateSkill::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
