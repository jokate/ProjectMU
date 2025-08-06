// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_CharacterJump.h"
#include "Data/MUEnum.h"
#include "MUGA_CastPaint.generated.h"

class UNNEModelData;
/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_CastPaint : public UGameplayAbility_CharacterJump
{
	GENERATED_BODY()

public :
	UMUGA_CastPaint();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	virtual void CastPaint( const TArray<float>& OutputData );
public :
	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<UNNEModelData> ModelData;

	UPROPERTY( EditDefaultsOnly )
	FGameplayTag WidgetTag;

	UPROPERTY( EditDefaultsOnly )
	TArray<ESkillSlotType> PainterSkillSlotType;

	UPROPERTY( EditDefaultsOnly )
	float MinimumThreshold = 5.0f;
};
