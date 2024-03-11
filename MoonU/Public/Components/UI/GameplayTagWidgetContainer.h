// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DataTable/MUWidgetToCheck.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "UI/MUWidget.h"
#include "GameplayTagWidgetContainer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UGameplayTagWidgetContainer : public UActorComponent, public IGameplayTagWidgetOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameplayTagWidgetContainer();

#pragma region IGameplayTagWidgetOwner
	virtual UUserWidget* GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;
	
	virtual void ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual void HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;
	
	virtual bool IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag) override;

	virtual bool IsGameplayWidgetInViewport() override;

	virtual void HideAllWidgetForGameplay() override;
#pragma endregion

	const bool CheckContainsWidget(const FGameplayTag& InGameplayTag);
public:
protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayTag For Gameplay Widget")
	TObjectPtr<UMUWidgetToCheck> GameplayTagForGameplay;
	
	UPROPERTY(Transient, VisibleAnywhere, Category = "GameplayTag Widget | Instances")
	TMap<FGameplayTag, UUserWidget*> WidgetContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayTag Widget | Classes")
	TMap<FGameplayTag, TSubclassOf<UUserWidget>> WidgetClassMapping;

	
};
