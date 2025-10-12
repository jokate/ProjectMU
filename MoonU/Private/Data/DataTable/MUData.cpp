// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataTable/MUData.h"

void FMUInputCommandList::ConsumeInput(ECombatInputType InputType )
{
	// 정학한 순서대로 들어와야 하는경우. 인덱스 여부 판단.
	if ( bExactlyMatch )
	{
		if (InputTypes.IsValidIndex(ProcessIndex) == true && InputTypes[ProcessIndex] == InputType )
		{
			++ProcessIndex;
		}
		else
		{
			bCanConsume = false;
		}
	}
	else
	{
		
		if (InputTypes.Contains(InputType) == true )
		{
			++ProcessIndex;
		}
		else
		{
			bCanConsume = false;
		}
	}
}

bool FMUInputCommandList::CanConsumeInput() const
{
	return bCanConsume;
}

// 모든 처리가 완료되었을 시, 처리.
bool FMUInputCommandList::CanProcessInput() const
{
	return ProcessIndex == InputTypes.Num() - 1;
}
