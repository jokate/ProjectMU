// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MUEnum.h"
#include "MUSkillTreeWidget.generated.h"

class UVerticalBox;
class UOverlay;
class UTextBlock;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSkillTreeClicked, ESkillSlotType, SlotType );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAttributeTreeClicked, FName, SlotName );

UCLASS()
class MOONU_API UMUSkillTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void SetupCharacterID( FName InCharacterID );

	virtual void SetupCharacterID( int32 InCharacterID );

	UFUNCTION()
	virtual void OnEnforcementUpdated();

	virtual void InitializeWidget();

	UFUNCTION()
	virtual void SkillTreeClicked( ESkillSlotType SlotType );

	UFUNCTION()
	virtual void AttributeTreeClicked(FName SlotName);

public :
	UPROPERTY( BlueprintAssignable, BlueprintCallable)
	FOnSkillTreeClicked OnSkillTreeClicked;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAttributeTreeClicked OnAttributeTreeClicked;
	
public :
	UPROPERTY( BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UTextBlock> CurrentCostText;

	UPROPERTY( BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UVerticalBox> SkillSlotVertical;

	UPROPERTY( BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UVerticalBox> AttributeSlotVertical;
	
	UPROPERTY()
	int32 CharacterID = 0;
};
