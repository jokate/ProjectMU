// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_Trace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MUDefines.h"
#include "Abilities/GameplayAbility.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "Interface/MUPlayer.h"
#include "Library/MUFunctionLibrary.h"


class IGenericTeamAgentInterface;
// Sets default values
AMUTA_Trace::AMUTA_Trace()
{
	RootCollisionComponent = CreateDefaultSubobject<USceneComponent>("RootCollisionComponent");
	SetRootComponent(RootCollisionComponent);
}

void AMUTA_Trace::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<USceneComponent*> ChildrenComponents;
	RootCollisionComponent->GetChildrenComponents(true, ChildrenComponents);

	for ( USceneComponent* Child : ChildrenComponents )
	{
		UShapeComponent* ShapeComponent = Cast<UShapeComponent>(Child);

		if ( IsValid(ShapeComponent) )
		{
			ShapeComponent->SetCollisionProfileName(TEXT("Weapon"));
			ShapeComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
			DamageShapes.Add(ShapeComponent);
		}
	}
}

void AMUTA_Trace::BeginPlay()
{
	Super::BeginPlay();

	if ( IsValid(SourceActor) )
	{
		AttachToActor(SourceActor, FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
	}
}

void AMUTA_Trace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(MU_EVENT_TRACEEND);
	}

	if ( IsValid(SourceActor) )
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AMUTA_Trace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceStart();
}

void AMUTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);

	if (!ASC)
	{
		return;	
	}

	ASC->GenericGameplayEventCallbacks.FindOrAdd(MU_EVENT_TRACEEND).AddUObject(this, &ThisClass::OnAnimNotifyStateEnd);
}

FGameplayAbilityTargetDataHandle AMUTA_Trace::MakeTargetData()
{
	return FGameplayAbilityTargetDataHandle();
}

void AMUTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		
		if (TargetDataReadyDelegate.IsBound())
		{
			TargetDataReadyDelegate.Broadcast(DataHandle);
		}
	}
}

void AMUTA_Trace::OnAnimNotifyStateEnd(const FGameplayEventData* EventData)
{
	ConfirmTargeting();
}

void AMUTA_Trace::TraceStart()
{
	//Redefine : 2026-03-01 : Check All Shape Overlap Actors

	TArray<FHitResult> HitResults;
	for ( UShapeComponent* DamageShape : DamageShapes )
	{
		TArray<FOverlapInfo> OverlapInfos = DamageShape->GetOverlapInfos();

		for ( FOverlapInfo& OverlapInfo : OverlapInfos )
		{
			FHitResult HitResult = OverlapInfo.OverlapInfo;

			if (SourceActor && HitResult.GetActor())
			{
				continue;
			}

			HitResults.Add(HitResult);
		}
	}

	ProcessHitResult(HitResults);
}

void AMUTA_Trace::InitializeData(const FName& InTargetDamageInfo)
{
	TargetDamageInfo = InTargetDamageInfo;
}

void AMUTA_Trace::ProcessHitResult(const TArray<FHitResult>& HitResults)
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	
	const IGenericTeamAgentInterface* SourceActorTeam = CastChecked<IGenericTeamAgentInterface>(SourceActor);

	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character);
	
	for (const auto& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (SourceActorTeam->GetTeamAttitudeTowards(*HitActor) != ETeamAttitude::Hostile)
			{
				continue;
			}
			
			if (!QueryActors.Contains(HitActor))
			{
				QueryActors.Add(HitActor);

				// 쿼리 액터에 없는 경우 (판단이 아직 안된 객체의 경우 최초 감지 시, HitResult와 함께 넘겨준다.)
				
				FGameplayEventData GameplayEventData;
				GameplayEventData.Instigator = OwningAbility->GetAvatarActorFromActorInfo();
				FGameplayAbilityTargetData_SingleTargetHit* SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
				
				GameplayEventData.TargetData.Add(SingleTargetHit);

				//Hit가 된 캐릭터에게 즉각적으로 데미지를 가하는 로직.
				UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor);
				if ( IsValid(SourceASC) == true ) 
				{
					ProcessDamage(SourceASC, TargetASC);
				}
				
				//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, MU_EVENT_ONHIT, GameplayEventData);
			}
		}
	} 
}

void AMUTA_Trace::ProcessDamage(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC)
{
	FMUDamageInfo DamageInfo;
	if ( UMUFunctionLibrary::GetDamageInfo(this, TargetDamageInfo, DamageInfo) == false )
	{
		return;
	}

	const UMUCharacterAttributeSet* SourceAttributeSet = Cast<UMUCharacterAttributeSet>(SourceASC->GetAttributeSet(UMUCharacterAttributeSet::StaticClass()));
	const UMUCharacterAttributeSet* TargetAttributeSet = Cast<UMUCharacterAttributeSet>(TargetASC->GetAttributeSet(UMUCharacterAttributeSet::StaticClass()));

	if ( IsValid(SourceAttributeSet) == false || IsValid(TargetAttributeSet) == false )
	{
		return;
	}
	
	UMUCharacterAttributeSet* ModifiableTarget = const_cast<UMUCharacterAttributeSet*>(TargetAttributeSet);
	int32 FinalDamage = FMath::RoundToInt(DamageInfo.ConstantDamage + SourceAttributeSet->GetAttackDamage() * DamageInfo.DamageRatio);

	float CurHp = TargetAttributeSet->GetCurrentHp();
	float ExpectHp = CurHp - FinalDamage;

	ModifiableTarget->SetCurrentHp(FMath::Clamp(ExpectHp, 0.f, ExpectHp));

	// 사실상 공격구조에 대한 변동.
	ApplyBuff(SourceASC, SourceASC, DamageInfo.ApplyBuffToSource);
	ApplyBuff(SourceASC, TargetASC, DamageInfo.ApplyBuffToTarget);
}

void AMUTA_Trace::ApplyBuff(UAbilitySystemComponent* SourceASC, UAbilitySystemComponent* TargetASC, TSubclassOf<UGameplayEffect> BuffEffectClass)
{
	if ( IsValid(SourceASC) == false || IsValid(TargetASC) == false || BuffEffectClass == nullptr ) 
	{
		return;
	}
	
	FGameplayEffectContextHandle SourceEffectContext = SourceASC->MakeEffectContext();
	FGameplayEffectSpecHandle SourceEffectSpecHandle = SourceASC->MakeOutgoingSpec(BuffEffectClass, 1, SourceEffectContext);

	if (SourceEffectSpecHandle.IsValid())
	{
		SourceASC->ApplyGameplayEffectSpecToTarget(*SourceEffectSpecHandle.Data.Get(), TargetASC);
	}
}
