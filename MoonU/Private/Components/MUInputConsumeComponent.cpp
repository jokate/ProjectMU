// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MUInputConsumeComponent.h"

#include "Library/MUFunctionLibrary.h"


// Sets default values for this component's properties
UMUInputConsumeComponent::UMUInputConsumeComponent()
{
}


// Called when the game starts
void UMUInputConsumeComponent::BeginPlay()
{
	Super::BeginPlay();

	// 모든 데이터를 서칭해야 한다.
	UMUFunctionLibrary::GetAllInputCommandList(this, AllInputCommandLists);
	
	// 현재 관련 콤보 세팅? 혹은 그냥 State Tree 세팅?
	if ( GetNetMode() == NM_Client || GetNetMode() == NM_Standalone )
	{
		GetWorld()->GetTimerManager().SetTimer(InputConsumeTimer, this, &UMUInputConsumeComponent::ProcessConsumeInput, InputConsumeTimeInterval, true );	
	}
}

void UMUInputConsumeComponent::ProcessConsumeInput()
{
	// 커맨드에 대한 처리 분기.
	// Client Side 처리
	for ( ECombatInputType CombatInput : InputCombatQueue)
	{
		for ( FMUInputCommandList& InputCommandList : AllInputCommandLists )
		{
			if ( InputCommandList.CanProcessInput() == false )
			{
				continue;
			}

			InputCommandList.ConsumeInput(CombatInput);

			if ( InputCommandList.CanProcessInput() == true )
			{
				UE_LOG(LogTemp, Log, TEXT("Consume Input Tag : %s"), *InputCommandList.TargetGameplayTag.ToString());
				break;
			}
		}	
	}


	for ( FMUInputCommandList& InputCommandList : AllInputCommandLists )
	{
		InputCommandList.Reset();
	}

	InputCombatQueue.Empty();
}

void UMUInputConsumeComponent::MULTI_ConsumeInput_Implementation(FGameplayTag ConsumeTag)
{
	
}

void UMUInputConsumeComponent::SendInput(ECombatInputType CombatInput)
{
	InputCombatQueue.Add(CombatInput);	
}

