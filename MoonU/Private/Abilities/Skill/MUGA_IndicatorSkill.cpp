// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "MUDefines.h"
#include "Abilities/AT/MUAT_SpawnIndicator.h"
#include "Abilities/AT/MUAT_WaitTriggerInput.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/Input/MUEnhancedInputComponent.h"
#include "Indicator/MUIndicatorManageSubsystem.h"
#include "Library/MUFunctionLibrary.h"


class UAbilityTask_PlayMontageAndWait;

UMUGA_IndicatorSkill::UMUGA_IndicatorSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	CancelAbilitiesWithTag.AddTag(MU_SKILL_INDICATOR);
	ActivationOwnedTags.AddTag(MU_SKILL_INDICATOR);

	FMUInputStepData& StepData = InputPressedFunctor.FindOrAdd(1);
		
	FInstancedStruct& RightClick = StepData.InstancedStructContainer.AddDefaulted_GetRef();
	RightClick.InitializeAs(FAbilityInputAction_EndAbility::StaticStruct());

	FAbilityInputAction_EndAbility* InputAction_EndAbility = RightClick.GetMutablePtr<FAbilityInputAction_EndAbility>();
	InputAction_EndAbility->InputTagContainer.AddTag(MU_INPUT_DODGE);


	FInstancedStruct& LeftClick = StepData.InstancedStructContainer.AddDefaulted_GetRef();
	LeftClick.InitializeAs(FAbilityInputAction_CastSkill::StaticStruct());

	FAbilityInputAction_CastSkill* InputAction_CastSkill = LeftClick.GetMutablePtr<FAbilityInputAction_CastSkill>();
	InputAction_CastSkill->InputTagContainer.AddTag(MU_INPUT_LMATTACK);
}

void UMUGA_IndicatorSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if ( CanUseSkill() == false )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false );
		return;
	}

	UMUAT_SpawnIndicator* IndicatorSkill = UMUAT_SpawnIndicator::CreateTask(this, SkillID);

	if ( IsValid( IndicatorSkill ) == true)
	{
		IndicatorSkill->ReadyForActivation();
		OnSkillStateChanged.AddDynamic( IndicatorSkill, &UMUAT_SpawnIndicator::EndTask);
	}

	SetupReadyMontage();
}

void UMUGA_IndicatorSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	MontageTask = nullptr;
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::ActivateSkill()
{
	AActor* OwnerActor = GetAvatarActorFromActorInfo();

	if ( IsValid(OwnerActor) == false )
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}
	
	APlayerController* PC = OwnerPawn->GetController<APlayerController>();

	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer()))
	{
		TargetLocation = Subsystem->GetIndicatorTargetLocation( SkillID );
		TargetRotation = Subsystem->GetIndicatorTargetRotation( SkillID );

		UE_LOG(LogTemp, Log, TEXT("Rotation : %s"), *TargetRotation.ToString() )
	}

	UE_LOG(LogTemp, Log, TEXT("Skill Active"));
	
	Super::ActivateSkill();
}

void UMUGA_IndicatorSkill::SetupReadyMontage()
{
	AActor* OwnerActor = GetOwningActorFromActorInfo();

	UAnimMontage* ActiveMontage = SkillData.ReadySkillMontage.LoadSynchronous();

	if ( IsValid(ActiveMontage) == false )
	{
		return;
	}

	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Ready"), ActiveMontage,
	1.0f, NAME_None, true );

	MontageTask = NewTask;
	NewTask->ReadyForActivation();
}

void UMUGA_IndicatorSkill::CastSkill()
{
	if ( IsValid( MontageTask ) == true )
	{
		MontageTask->EndTask();	
	}
	
	ActivateSkill();
	
	ProcessStep();
}