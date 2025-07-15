// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "MUDefines.h"
#include "Components/Input/MUEnhancedInputComponent.h"
#include "Indicator/MUIndicatorManageSubsystem.h"
#include "Library/MUFunctionLibrary.h"


UMUGA_IndicatorSkill::UMUGA_IndicatorSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
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
	
	// Input에 대한 바인딩 처리 필요.
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
	
	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}
	
	UInputConfig* InputConfig = UMUFunctionLibrary::GetInputConfigByOwner( GetAvatarActorFromActorInfo() );

	if ( IsValid(InputConfig) == false )
	{
		return;
	}

	const UInputAction* InputAction = InputConfig->FindInputActionForTag(MU_INPUT_SIMPLE_CAST);

	if ( IsValid( InputAction ) == true )
	{
		EnhancedInputComponent->BindAction( InputAction, ETriggerEvent::Triggered, this, &UMUGA_IndicatorSkill::OnSkillInputPressed);	
	}

	const UInputAction* CancelAction = InputConfig->FindInputActionForTag(MU_INPUT_CANCEL);

	if ( IsValid( CancelAction ) == true )
	{
		EnhancedInputComponent->BindAction( CancelAction, ETriggerEvent::Triggered, this, &UMUGA_IndicatorSkill::OnSkillCanceled);	
	}

	APlayerController* PC = OwnerPawn->GetController<APlayerController>();

	if ( IsValid( PC ) == false )
	{
		return;
	}
	
	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer()))
	{
		Subsystem->ActivateSkillIndicator( SkillID );
	}
}

void UMUGA_IndicatorSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::ActivateSkill()
{
	Super::ActivateSkill();
	
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
	

	ResetInput();

	UE_LOG(LogTemp, Log, TEXT("Skill Active"));
}


void UMUGA_IndicatorSkill::OnSkillInputPressed()
{
	ActivateSkill();
}

void UMUGA_IndicatorSkill::OnSkillCanceled()
{
	ResetInput();
	
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::ResetInput()
{
	// Input에 대한 바인딩 처리 필요.
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
	
	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}

	EnhancedInputComponent->ClearBindingsForObject( this );

	APlayerController* PC = OwnerPawn->GetController<APlayerController>();
	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer()))
	{
		Subsystem->DeactivateSkillIndicator( SkillID );
	}
}
