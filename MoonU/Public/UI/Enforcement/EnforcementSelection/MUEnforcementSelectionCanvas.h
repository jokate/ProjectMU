// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MUEnum.h"
#include "MUEnforcementSelectionCanvas.generated.h"

class UHorizontalBox;
class UMUEnforcementSelectionWidget;

/**
 * 
 */
UCLASS()
class MOONU_API UMUEnforcementSelectionCanvas : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION()
	virtual void SetCharacterID( FName InCharacterID );
	virtual void SetCharacterID( int32 InCharacterID );
	virtual void SetupAttribute( FName AttributeSlotName );
	virtual void SetupSkillAttribute( ESkillSlotType InSkillSlot );
	virtual void AddSelectionMember();

	UFUNCTION()
	void OnEnforcementSelected();
	
public :
	UPROPERTY( EditAnywhere, meta = (BindWidget) )
	TObjectPtr<UHorizontalBox> EnforcementSelectionHorizontal;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float PaddingValue = 30.f;

	UPROPERTY( BlueprintReadOnly )
	int32 CharacterID;

	// 강화 관련한 요소 옵션.
	UPROPERTY( BlueprintReadOnly )
	TEnumAsByte<EEnforcementType> EnforcementType;

	UPROPERTY( BlueprintReadOnly )
	FName EnforcementSlotName;

	UPROPERTY( BlueprintReadOnly )
	ESkillSlotType SkillSlotType;
};
