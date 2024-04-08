// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_Attack.h"

#include "MotionWarpingComponent.h"
#include "MUDefines.h"
#include "Character/MUCharacterPlayer.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Data/Animation/MUComboActionData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

UMUGA_Attack::UMUGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
}

void UMUGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AMUCharacterPlayer* CharacterPlayer = CastChecked<AMUCharacterPlayer>(ActorInfo->AvatarActor.Get());
	CurrentComboData = CharacterPlayer->GetComboActionData();
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayCombo"), CurrentComboData->AnimMontage, 1.0f, GetNextSection());
	PlayAttackTask->OnCompleted.AddDynamic(this, &ThisClass::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &ThisClass::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
	StartComboTimer();
}

void UMUGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMUGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AMUCharacterPlayer* CharacterPlayer = CastChecked<AMUCharacterPlayer>(ActorInfo->AvatarActor.Get());
	CharacterPlayer->GetMotionWarpingComponent()->RemoveWarpTarget(COMBO_MOTION_WARP);
	CurrentCombo = 0;
	CurrentComboData = nullptr;
	HasNextComboInput = false;
}

void UMUGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!ComboTimerHandle.IsValid()) 
	{
		HasNextComboInput = false;
	}
	else
	{
		HasNextComboInput = true;
	}
}

void UMUGA_Attack::OnCompleteCallback()
{
	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_Attack::OnInterruptedCallback()
{
	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

FName UMUGA_Attack::GetNextSection()
{
	CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, CurrentComboData->MaxComboCount);
	FName NextSection = *FString::Printf(TEXT("%s%d"), *CurrentComboData->MontageSectionNamePrefix, CurrentCombo);
	return NextSection;
}

void UMUGA_Attack::StartComboTimer()
{
	//배열에 따라서 현재 콤보에 대해서 - 1
	int32 ComboIndex = CurrentCombo - 1;
	//혹시 제대로 된 Index인지에 대한 검증
	ensure(CurrentComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	//입력까지 기다리는 시간
	const float ComboEffectiveTime = CurrentComboData->EffectiveFrameCount[ComboIndex] / CurrentComboData->FrameRate;

	//대기 시간이 있는 경우에는 Timer을 돌려서 제대로 된 Input이 있는지를 검증한다.
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ThisClass::CheckComboInput, ComboEffectiveTime, false);
	}
}


void UMUGA_Attack::CheckComboInput()
{
	//제한 시간이 되었다면 Timer에 대해서 Invalidate를 하고
	ComboTimerHandle.Invalidate();

	//만약 이전에 입력이 들어온 경우에는 다음으로 넘어가준다.=
	if (HasNextComboInput)
	{
		//근데 이 함수는 좀 생소하긴 한데 몽타쥬를 점프시키는 함수
		MontageJumpToSection(GetNextSection());
		StartComboTimer();
		HasNextComboInput = false;
	}
}