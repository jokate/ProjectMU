// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Input/MUEnhancedInputComponent.h"

const FGameplayTag& UMUEnhancedInputComponent::GetGameplayTagByInputAction(const UInputAction* InputAction)
{
	const FInputActionWrapper InputActionWrapper(InputAction);

	if (!InputGameplayTagMap.Contains(InputActionWrapper))
	{
		return FGameplayTag::EmptyTag;
	}

	return InputGameplayTagMap[InputActionWrapper]; 
}
