// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_Trace.h"

#include "AbilitySystemComponent.h"
#include "Abilities/TA/MUTA_BoxTrace.h"
#include "Abilities/TA/MUTA_CapsuleTrace.h"
#include "Abilities/TA/MUTA_SphereTrace.h"
#include "Abilities/TA/MUTA_Trace.h"
#include "Library/MUFunctionLibrary.h"

UMUAT_Trace::UMUAT_Trace()
{
	
}

UMUAT_Trace* UMUAT_Trace::CreateTask(UGameplayAbility* OwningAbility, const FName& TargetDamageInfo )
{
	UMUAT_Trace* NewTask = NewAbilityTask<UMUAT_Trace>(OwningAbility);
	NewTask->TargetDamageInfo = TargetDamageInfo;
	return NewTask;
}

void UMUAT_Trace::Activate()
{
	Super::Activate();
	SetupTraceData();
	SetWaitingOnAvatar();
}

void UMUAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_Trace::SetupTraceData()
{
	AActor* AvatarActor = GetAvatarActor();
	FMUDamageInfo DamageInfo;
	if ( UMUFunctionLibrary::GetDamageInfo(this, TargetDamageInfo, DamageInfo) == false  || IsValid(AvatarActor) == false )
	{
		OnComplete.Broadcast(FGameplayAbilityTargetDataHandle());
		return;
	}

	for ( const FMUDamageRange& DamageRange : DamageInfo.DamageRanges )
	{
		TSubclassOf<AMUTA_Trace> TraceClass = DamageRange.TraceClass;
		const FInstancedStruct& RangeConfig = DamageRange.RangeConfig;

		AMUTA_Trace* Trace = SpawnAndInitializeTargetActor(TraceClass);

		if ( IsValid(Trace) == false )
		{
			continue;
		}
		FTransform FinalTransform = AvatarActor->GetActorTransform();
		FName AttachmentSocket = NAME_None;
		if (AMUTA_BoxTrace* BoxTrace = Cast<AMUTA_BoxTrace>(Trace))
		{
			const FMUTraceRangeConfig_Box* Cfg = RangeConfig.GetPtr<FMUTraceRangeConfig_Box>();
			if ( Cfg != nullptr )
			{
				FinalTransform += Cfg->OffSetTransform;
				AttachmentSocket = Cfg->AttachmentSocketName;
				BoxTrace->SetupBoxExtent(Cfg->BoxExtent);
			}
		}

		if ( AMUTA_CapsuleTrace* CapsuleTrace = Cast<AMUTA_CapsuleTrace>(Trace))
		{
			const FMUTraceRangeConfig_Capsule* Cfg = RangeConfig.GetPtr<FMUTraceRangeConfig_Capsule>();

			if ( Cfg != nullptr )
			{
				FinalTransform += Cfg->OffSetTransform;
				AttachmentSocket = Cfg->AttachmentSocketName;
				CapsuleTrace->SetupCapsule(Cfg->HalfHeight, Cfg->Radius);
			}
		}

		if ( AMUTA_SphereTrace* SphereTrace = Cast<AMUTA_SphereTrace>(Trace))
		{
			const FMUTraceRangeConfig_Sphere* Cfg = RangeConfig.GetPtr<FMUTraceRangeConfig_Sphere>();

			if ( Cfg != nullptr )
			{
				FinalTransform += Cfg->OffSetTransform;
				AttachmentSocket = Cfg->AttachmentSocketName;
				SphereTrace->SetupRadius(Cfg->Radius);
			}
		}

		FinalizeTargetActor(Trace, FinalTransform, AttachmentSocket);
	}
}

AMUTA_Trace* UMUAT_Trace::SpawnAndInitializeTargetActor(TSubclassOf<AMUTA_Trace> TraceClass)
{
	AMUTA_Trace* SpawnedTargetActor = Cast<AMUTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TraceClass, FTransform::Identity,
nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UMUAT_Trace::OnTargetDataReadyCallback);
		SpawnedTargetActor->InitializeData(TargetDamageInfo);
	}

	return SpawnedTargetActor;
}

void UMUAT_Trace::FinalizeTargetActor(AMUTA_Trace* TraceTarget, const FTransform& FinalizeTransform, const FName& AttachmentSocket)
{
	ACharacter* AvatarActor = Cast<ACharacter>(GetAvatarActor());
	USkeletalMeshComponent* SkeletalComponent = AvatarActor->GetMesh();
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();

	if ( IsValid(AvatarActor) == false || IsValid(SkeletalComponent) == false || IsValid(ASC) == false )
	{
		return;
	}
	
	TraceTarget->FinishSpawning(FinalizeTransform);
	ASC->SpawnedTargetActors.Push(TraceTarget);
	TraceTarget->StartTargeting(Ability);
	TraceTarget->AttachToComponent(SkeletalComponent,
		AttachmentSocket == NAME_None ?
		FAttachmentTransformRules::KeepWorldTransform
		: FAttachmentTransformRules::SnapToTargetIncludingScale
		, AttachmentSocket);
	
	SpawnedTargetActors.AddUnique(TraceTarget);
}

void UMUAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
