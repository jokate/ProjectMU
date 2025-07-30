// Fill out your copyright notice in the Description page of Project Settings.


#include "Training/PainterCanvasWidget.h"

#include "Components/Button.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Training/DataExtractorWidget.h"

void UPainterCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(PaintButton) )
	{
		PaintButton->OnClicked.AddDynamic( this, &UPainterCanvasWidget::OnPaintButtonPressed );
	}
}

void UPainterCanvasWidget::OnPaintButtonPressed()
{
	if ( IsValid(DataExtractorWidget) )
	{
		DataExtractorWidget->ResetAllMember();
	}  
}
