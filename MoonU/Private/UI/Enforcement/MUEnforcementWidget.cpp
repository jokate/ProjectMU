// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUEnforcementWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Library/MUFunctionLibrary.h"

void UMUEnforcementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(SelectionButton) == true )
	{
		SelectionButton->OnClicked.AddDynamic( this, &UMUEnforcementWidget::OnSelectionButtonClicked );
	}
}

void UMUEnforcementWidget::SetupWidgetInfo()
{
	FMUEnforcementData EnforcementData;
	if ( UMUFunctionLibrary::GetEnforcementData(this, AllocatedEnforcementID, EnforcementData) == true )
	{
		PortraitImage->SetBrushFromTexture(EnforcementData.DescriptionIcon);
	} 
}

void UMUEnforcementWidget::OnSelectionButtonClicked_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Log : Selection Button Clicked"));

	//강화 관련한 위젯에 대한 부분이 나와야 할 것으로 보이는데, 내부 정보 처리에 의한 작업 처리가 필요 한듯. (코드 화 필요 )
}
