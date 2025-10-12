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
	TArray<FMUInputCommandList> TempInputCommandLists = AllInputCommandLists;

	bool bHasProcessedCombo = false;
	while ( InputCombatQueue.Num() > 0 )
	{
		if ( bHasProcessedCombo == true )
		{
			break;
		}
		
		ECombatInputType FirstInput = InputCombatQueue.Pop();
		TArray<FMUInputCommandList> PendingToRemoveCommands;
		
		for ( FMUInputCommandList& InputCommandList : TempInputCommandLists )
		{
			if ( InputCommandList.CanProcessInput() == false )
			{
				PendingToRemoveCommands.Add(InputCommandList);
				continue;
			}

			InputCommandList.ConsumeInput(FirstInput);

			if ( InputCommandList.CanProcessInput() == true )
			{
				UE_LOG(LogTemp, Log, TEXT("Consume Input Tag : %s"), *InputCommandList.TargetGameplayTag.ToString());
				// 이 부분에서 실질적 처리 필요.
				bHasProcessedCombo = true;
				break;
			}
		}

		for ( FMUInputCommandList& InputCommandList : PendingToRemoveCommands )
		{
			TempInputCommandLists.Remove(InputCommandList);
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
	UE_LOG(LogTemp, Log, TEXT("UMUInputConsumeComponent::SendInput %d"), CombatInput);
	InputCombatQueue.Add(CombatInput);	
}

