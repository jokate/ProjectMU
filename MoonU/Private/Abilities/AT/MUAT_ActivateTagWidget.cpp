// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_ActivateTagWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"

UMUAT_ActivateTagWidget* UMUAT_ActivateTagWidget::CreateTask(UGameplayAbility* InAbility, FGameplayTag InWidgetTag)
{
	UMUAT_ActivateTagWidget* NewTask = NewAbilityTask<UMUAT_ActivateTagWidget>(InAbility);
	NewTask->WidgetTag = InWidgetTag;

	return NewTask;
}

void UMUAT_ActivateTagWidget::Activate()
{
	Super::Activate();

	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	APlayerController* PlayerController = OwnerActor->GetInstigatorController<APlayerController>();

	if ( IsValid( PlayerController ) == false )
	{
		return;
	}

	IGameplayTagWidgetOwner* GameplayTagWidgetOwner = Cast<IGameplayTagWidgetOwner>(PlayerController->GetHUD());

	if ( GameplayTagWidgetOwner == nullptr)
	{
		return;
	}

	GameplayTagWidgetOwner->ShowWidgetByGameplayTag(WidgetTag);
	
	TagWidget = GameplayTagWidgetOwner->GetWidgetByGameplayTag(WidgetTag);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx( PlayerController );
	PlayerController->bShowMouseCursor = true;
}

void UMUAT_ActivateTagWidget::OnDestroy(bool bInOwnerFinished)
{
	AActor* OwnerActor = GetOwnerActor();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	APlayerController* PlayerController = OwnerActor->GetInstigatorController<APlayerController>();

	if ( IsValid( PlayerController ) == false )
	{
		return;
	}

	IGameplayTagWidgetOwner* GameplayTagWidgetOwner = Cast<IGameplayTagWidgetOwner>(PlayerController->GetHUD());

	if ( GameplayTagWidgetOwner == nullptr)
	{
		return;
	}

	GameplayTagWidgetOwner->HideWidgetByGameplayTag(WidgetTag);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly( PlayerController );
	PlayerController->bShowMouseCursor = false;
	Super::OnDestroy(bInOwnerFinished);
}
