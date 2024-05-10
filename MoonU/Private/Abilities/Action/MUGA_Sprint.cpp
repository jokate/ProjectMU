// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_Sprint.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUGA_Sprint::UMUGA_Sprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();

	if (MovementComponent == nullptr)
	{
		return;
	}

	MovementComponent->MaxWalkSpeed = SPRINT_SPEED;

	FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(GameplayEffectClass);

	if (EffectSpec.IsValid())
	{
		ActivateEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo,EffectSpec);
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSet::GetCurrentStaminaAttribute()).AddUObject(this, &UMUGA_Sprint::OnChangedAttribute);
	}
}


void UMUGA_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UMUGA_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();

	if (MovementComponent == nullptr)
	{
		return;
	}

	MovementComponent->MaxWalkSpeed = WALK_SPEED;

	if (ActivateEffectHandle.IsValid())
	{
		BP_RemoveGameplayEffectFromOwnerWithHandle(ActivateEffectHandle);
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSet::GetCurrentStaminaAttribute()).RemoveAll(this);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UMUGA_Sprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor == nullptr)
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(TargetActor);

	if (Character == nullptr)
	{
		return false;
	}
	
	bResult &= !Character->GetVelocity().IsNearlyZero();

	return bResult;
}

void UMUGA_Sprint::OnChangedAttribute(const FOnAttributeChangeData& Payload)
{
	if (Payload.NewValue <= 0.0f)
	{
		bool bReplicated = true;
		bool bWasCancelled = false;

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicated, bWasCancelled);
	}
}
