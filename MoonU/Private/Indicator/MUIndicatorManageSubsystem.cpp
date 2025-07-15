// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUIndicatorManageSubsystem.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
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

void UMUIndicatorManageSubsystem::SetupCamera(FName IndicatorID)
{
	if ( IsValid( LocalPlayerController) == false || IsValid(LocalPlayerActor) == false )
	{
		return;
	}
	
	FMUSkillData SkillData;
	// 가정. 스킬에 대한 부분에 대해서 호출
	if ( UMUFunctionLibrary::GetSkillData( this, IndicatorID, SkillData) == false )
	{
		return;
	}
	
	if ( IsValid(IndicatorCameraActor) == false )
	{
		ACameraActor* CamActor = GetWorld()->SpawnActorDeferred<ACameraActor>(ACameraActor::StaticClass(), LocalPlayerActor->GetActorTransform());

		if ( IsValid( CamActor ) == false )
		{
			return;
		}

		IndicatorCameraActor = CamActor;
		FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules( EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,  EAttachmentRule::SnapToTarget, false );
		IndicatorCameraActor->AttachToActor( LocalPlayerActor, AttachmentRule );
		UCameraComponent* IndicatorCameraComponent = IndicatorCameraActor->GetCameraComponent();
		UCameraComponent* PlayerCam = LocalPlayerActor->FindComponentByClass<UCameraComponent>();

		if ( IsValid(IndicatorCameraComponent) && IsValid(PlayerCam) )
		{
			IndicatorCameraComponent->FieldOfView = PlayerCam->FieldOfView;
			IndicatorCameraComponent->AspectRatio = PlayerCam->AspectRatio;
			IndicatorCameraComponent->bConstrainAspectRatio = PlayerCam->bConstrainAspectRatio;
			IndicatorCameraComponent->ProjectionMode = PlayerCam->ProjectionMode;

			IndicatorCameraComponent->PostProcessSettings = PlayerCam->PostProcessSettings;
			IndicatorCameraComponent->PostProcessBlendWeight = PlayerCam->PostProcessBlendWeight;
		}
		
	}

	IndicatorCameraActor->SetActorRelativeLocation(SkillData.IndicatorCameraOffSet);
	IndicatorCameraActor->SetActorRelativeRotation(SkillData.IndicatorCameraRotation);

	LocalPlayerController->SetViewTargetWithBlend( IndicatorCameraActor, 0.3f );
}

void UMUIndicatorManageSubsystem::DeactivateCamera()
{
	if ( IsValid( LocalPlayerController) == false || IsValid(LocalPlayerActor) == false || IsValid(IndicatorCameraActor) == false)
	{
		return;
	}

	LocalPlayerController->SetViewTargetWithBlend( LocalPlayerActor, 0.3f );
}

FVector UMUIndicatorManageSubsystem::GetIndicatorTargetLocation(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );
    
    if ( IsValid( SkillIndicator ) == false )
    {
    	return FVector::ZeroVector;
    }

	return SkillIndicator->GetTargetLocation();
}

FRotator UMUIndicatorManageSubsystem::GetIndicatorTargetRotation(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );
    
	if ( IsValid( SkillIndicator ) == false )
	{
		return FRotator::ZeroRotator;
	}

	return SkillIndicator->GetTargetRotation();
}

void UMUIndicatorManageSubsystem::ActivateSkillIndicator(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );

	if ( IsValid( SkillIndicator ) == false )
	{
		return;
	}

	SkillIndicator->ActivateSkillIndicator();

	SetupCamera( IndicatorID );

	bIsSkillMode = true;
}

void UMUIndicatorManageSubsystem::DeactivateSkillIndicator(FName IndicatorID)
{
	AMUSkillIndicator* SkillIndicator = GetIndicatorByID( IndicatorID );

	if ( IsValid( SkillIndicator ) == false )
	{
		return;
	}

	SkillIndicator->DeactivateSkillIndicator();

	DeactivateCamera();

	bIsSkillMode = false;
}

