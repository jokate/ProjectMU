// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AbilityAnimNotify/MUAnimNotify_SpawnAttackEntity.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AT/AttackSpawnTask/MUAT_SpawnAttackEntity.h"
#include "Interface/SkillActivateAbility.h"

void UMUAnimNotify_SpawnAttackEntity::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UGameplayAbility* Ability = GetCurrentAbility(MeshComp);

	if (IsValid(Ability) == false )
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();

	if ( IsValid(Owner) == false )
	{
		return;
	}
	
	if ( ISkillActivateAbility* SkillAbil = Cast<ISkillActivateAbility>(Ability) )
	{
		FTransform SpawnTransform = bUseFixedPos ? Owner->GetActorTransform() * FixedOffSet : SkillAbil->GetTargetTransform();

		UMUAT_SpawnAttackEntity* SpawnAttackEntity = UMUAT_SpawnAttackEntity::StartSpawnAttackEntity(Ability, SkillAbil->GetSkillID(), SpawnTransform);
		// 어차피 단순 스폰이니까 그대로 처리.... ( 근데 만약에 스폰이 완료되었다는 가정이라면? )
		SpawnAttackEntity->ReadyForActivation();
	}
}
