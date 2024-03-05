// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/MUGameSettings.h"

const UMUGameSettings* UMUGameSettings::Get()
{
	if (GameSettingInstance == nullptr)
	{
		GameSettingInstance = GetMutableDefault<UMUGameSettings>();
	}

	return GameSettingInstance;
}
