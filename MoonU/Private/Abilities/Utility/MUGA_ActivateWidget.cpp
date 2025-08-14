// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_ActivateWidget.h"

#include "Abilities/AT/MUAT_ActivateTagWidget.h"

void UMUGA_ActivateWidget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_ActivateTagWidget* ActivateTagWidget = UMUAT_ActivateTagWidget::CreateTask(this, WidgetGameplayTag);

	if ( IsValid(ActivateTagWidget) == true )
	{
		ActivateTagWidget->ReadyForActivation();
	}
}

void UMUGA_ActivateWidget::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false );
}

void UMUGA_ActivateWidget::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false );
}
