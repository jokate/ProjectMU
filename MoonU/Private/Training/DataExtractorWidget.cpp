// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonU/Public/Training/DataExtractorWidget.h"

#include "Engine/DataTable.h"

void UDataExtractorWidget::AddRowForTrainingInfo(UDataTable* InfoDataTable, FName InRowName, FString FileName)
{
	if (IsValid(InfoDataTable) == false)
	{
		return;
	}

	/*FTrainingDataTable* TrainingData = InfoDataTable->FindRow<FTrainingDataTable>(InRowName, "");

	if (TrainingData == nullptr)
	{
		return;
	}

	FTrainingDataTable TmpTrainingData = *TrainingData;

	TmpTrainingData.FileString.Add(FileName);

	InfoDataTable->AddRow(InRowName, TmpTrainingData);*/
}
