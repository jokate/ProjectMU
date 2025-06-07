// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUIndicatorManageSubsystem.h"

#include "Data/DataTable/MUData.h"
#include "Library/MUFunctionLibrary.h"

bool UMUIndicatorManageSubsystem::RegisterIndicator( FName IndicatorID )
{
	if ( IndicatorManagement.Contains(IndicatorID) == true )
	{
		return false;
	}

	if ( IsValid( LocalPlayerActor ) == false )
	{
		LocalPlayerActor = LocalPlayerController->GetPawn();

		if ( IsValid( LocalPlayerActor ) == false )
		{
			return false;
		}
	}
	
	FMUSkillData SkillData;
	// 가정. 스킬에 대한 부분에 대해서 호출
	if ( UMUFunctionLibrary::GetSkillData( this, IndicatorID, SkillData) == false )
	{
		return false;
	}
 	
	AMUSkillIndicator* SkillIndicator = GetWorld()->SpawnActorDeferred<AMUSkillIndicator>( SkillData.SkillIndicatorClass, LocalPlayerActor->GetActorTransform() );

	// 데이터 처리.
	SkillIndicator->SetupIndicatorInfo( LocalPlayerController, SkillData.CastingRange, SkillData.CastingAOE );
	
	SkillIndicator->FinishSpawning( LocalPlayerActor->GetActorTransform());
	FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules( EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,  EAttachmentRule::SnapToTarget, false );
	
	SkillIndicator->AttachToActor( LocalPlayerActor, AttachmentRule, TEXT("IndicatorSpawn") );
	IndicatorManagement.Add(IndicatorID, SkillIndicator);

	return true;
}

void UMUIndicatorManageSubsystem::UnRegisterIndicator(FName IndicatorID)
{
	if ( IndicatorManagement.Contains(IndicatorID) == true )
	{
		AMUSkillIndicator* SkillIndicator = IndicatorManagement[IndicatorID];

		SkillIndicator->Destroy();
		SkillIndicator = nullptr;

		IndicatorManagement.Remove(IndicatorID);
	}
}

AMUSkillIndicator* UMUIndicatorManageSubsystem::GetIndicatorByID(FName IndicatorID)
{
	if ( HasIndicator(IndicatorID) == false)
	{
		bool bResult = RegisterIndicator(IndicatorID);

		if ( bResult == false )
		{
			return nullptr;
		}
	}
	
	return IndicatorManagement[IndicatorID];
}

void UMUIndicatorManageSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	UE_LOG( LogTemp, Log, TEXT("Player Controller Set"));

	if ( IsValid(NewPlayerController ) == false )
	{
		return;
	}

	LocalPlayerController = NewPlayerController;
}

void UMUIndicatorManageSubsystem::ActivateSkillIndicator(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );

	if ( IsValid( SkillIndicator ) == false )
	{
		return;
	}

	SkillIndicator->ActivateSkillIndicator();
}

void UMUIndicatorManageSubsystem::DeactivateSkillIndicator(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );

	if ( IsValid( SkillIndicator ) == false )
	{
		return;
	}

	SkillIndicator->DeactivateSkillIndicator();
}

