// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_MakeNoise.h"

void UAnimNotify_MakeNoise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APawn* OwnerPawn = MeshComp->GetOwner<APawn>();

	if (OwnerPawn)
	{
		OwnerPawn->MakeNoise(1.0f, OwnerPawn, OwnerPawn->GetActorLocation());
	}
}
