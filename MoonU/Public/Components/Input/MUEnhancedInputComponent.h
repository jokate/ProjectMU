// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/InputConfig.h"
#include "MUEnhancedInputComponent.generated.h"

USTRUCT(BlueprintType)
struct FInputActionWrapper
{
	GENERATED_BODY()
	FInputActionWrapper() { InputAction = nullptr;}
	
	FInputActionWrapper(const UInputAction* InInputAction) {InputAction = InInputAction;}
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	const UInputAction* InputAction;

	bool operator==(const FInputActionWrapper& InputActionWrapper) const
	{
		return InputAction == InputActionWrapper.InputAction;
	}
};

FORCEINLINE uint32 GetTypeHash(const FInputActionWrapper& InInputActionWrapper)
{
	return FCrc::MemCrc32(&InInputActionWrapper, sizeof(FInputActionWrapper));
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType, typename VarType>
	void BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarType Var);
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	const FGameplayTag& GetGameplayTagByInputAction(const UInputAction* InputAction);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TMap<FInputActionWrapper, FGameplayTag> InputGameplayTagMap;

protected:
};

template <class UserClass, typename FuncType, typename VarType>
void UMUEnhancedInputComponent::BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarType Var)
{
	if (InputConfig == nullptr)
	{
		return;
	}
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func, Var);
		FInputActionWrapper Wrapper(IA);

		InputGameplayTagMap.Emplace(Wrapper,InputTag);
	}
}

template <class UserClass, typename FuncType>
void UMUEnhancedInputComponent::BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	if (InputConfig == nullptr)
	{
		return;
	}
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
		FInputActionWrapper Wrapper(IA);

		InputGameplayTagMap.Emplace(Wrapper,InputTag);
	}
}
