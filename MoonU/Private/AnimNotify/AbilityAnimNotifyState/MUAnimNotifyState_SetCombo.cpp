// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AbilityAnimNotifyState/MUAnimNotifyState_SetCombo.h"

#include "Abilities/GameplayAbility.h"
#include "Interface/SkillActivateAbility.h"

void UMUAnimNotifyState_SetCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	UGameplayAbility* GA = GetCurrentAbility(MeshComp);

	if ( IsValid(GA) == false )
	{
		return;
	}

	if ( ISkillActivateAbility* Skill = Cast<ISkillActivateAbility>(GA) )
	{
		if ( Skill->IsComboPressed() == true )
		{
			Skill->SetMontageSection(NextSection);
		}
	}
}
