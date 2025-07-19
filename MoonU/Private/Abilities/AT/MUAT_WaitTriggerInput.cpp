// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_WaitTriggerInput.h"

#include "Components/Input/MUEnhancedInputComponent.h"
#include "Library/MUFunctionLibrary.h"

UMUAT_WaitTriggerInput* UMUAT_WaitTriggerInput::CreateTask(UGameplayAbility* OwningAbility,
                                                           FGameplayTag InputGameplayTag, ETriggerEvent TriggerEvent)
{
	UMUAT_WaitTriggerInput* Task = NewAbilityTask<UMUAT_WaitTriggerInput>(OwningAbility);
	Task->GameplayTag = InputGameplayTag;
	Task->TriggerEvent = TriggerEvent;
	return Task;
}

void UMUAT_WaitTriggerInput::Activate()
{
	Super::Activate();

	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;	
	}

	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}
	
	UInputConfig* InputConfig = UMUFunctionLibrary::GetInputConfigByOwner( OwnerActor );

	if ( IsValid(InputConfig) == false )
	{
		return;
	}

	const UInputAction* InputAction = InputConfig->FindInputActionForTag(GameplayTag);

	if ( IsValid( InputAction ) == true )
	{
		EnhancedInputComponent->BindAction( InputAction, TriggerEvent, this, &UMUAT_WaitTriggerInput::OnInputPressed);	
	}
}

void UMUAT_WaitTriggerInput::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	ResetInput();
}

void UMUAT_WaitTriggerInput::OnInputPressed()
{
	if ( InputPressedCallback.IsBound() == true)
	{
		InputPressedCallback.Broadcast();
	}

	EndTask();
}

void UMUAT_WaitTriggerInput::ResetInput()
{
	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid(OwnerActor) == false )
	{
		return;
	}
	
	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}

	EnhancedInputComponent->ClearBindingsForObject( this );
}
