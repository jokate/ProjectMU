// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Painter/MUGA_CastPaint.h"

#include "Abilities/AT/MUAT_DrawingCanvas.h"
#include "Components/EnforcementComponent.h"

UMUGA_CastPaint::UMUGA_CastPaint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_CastPaint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_DrawingCanvas* DrawingCanvas = UMUAT_DrawingCanvas::CreateDrawingCanvas( this, ModelData, WidgetTag );

	if ( IsValid( DrawingCanvas ) == true )
	{
		DrawingCanvas->OnCanvasDrawingComplete.AddDynamic( this, &UMUGA_CastPaint::OnPaintComplete );
		DrawingCanvas->ReadyForActivation();
	}
}

void UMUGA_CastPaint::OnPaintComplete(const TArray<float>& OutputData)
{
	CastSkill( OutputData );

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false );
}

void UMUGA_CastPaint::CastSkill(const TArray<float>& OutputData)
{
	float MaxMem = FLT_MIN;
	int32 MaxIndex = -1;
	for ( int32 i = 0; i < OutputData.Num(); i++ )
	{
		if ( MaxMem > OutputData[i] )
		{
			MaxMem = OutputData[i];
			MaxIndex = i;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Max Target : %d"), MaxIndex + 1 );

	if ( MaxMem < MinimumThreshold )
	{
		return;
	}
    
	if ( PainterSkillSlotType.IsValidIndex(MaxIndex) == false )
	{
		return;
	}
    
	// 문양에 대한 스킬 캐스팅까지 연동 필요.

	AActor* OwnerActor = GetAvatarActorFromActorInfo();

	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}

	ISkillManager* SkillManager = Cast<ISkillManager>(OwnerActor);

	if ( SkillManager != nullptr )
	{
		SkillManager->TriggerInputSkill(PainterSkillSlotType[MaxIndex]);
	}
}
