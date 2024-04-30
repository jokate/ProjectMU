// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MUDefines.h"
#include "Camera/CameraComponent.h"
#include "Data/MUGameSettings.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/Input/MUEnhancedInputComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/AbilityInitComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/TimeWindComponent.h"
#include "Framework/MUPlayerState.h"
#include "Interface/TimeWinder.h"

// Sets default values
AMUCharacterPlayer::AMUCharacterPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComp"));
}

// Called when the game starts or when spawned
void AMUCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	const auto* GS = UMUGameSettings::Get();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (CameraMovementCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &AMUCharacterPlayer::OnTimelineProgressed);
		TimelineComponent->AddInterpFloat(CameraMovementCurve, TimelineProgress);
	}
}

void AMUCharacterPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMUCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMUPlayerState* PS = GetPlayerState<AMUPlayerState>();
	
	if (PS == nullptr)
	{
		return;
	}

	ASC = PS->GetAbilitySystemComponent();
	ASC->InitAbilityActorInfo(PS, this);

	AbilityInitComponent->InitAbilities();
}

void AMUCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

ETeamAttitude::Type AMUCharacterPlayer::GetTeamAttitudeTowards(const AActor& Other) const
{
	return ETeamAttitude::Hostile;
}

void AMUCharacterPlayer::OnTimelineProgressed(float Value)
{
	CameraBoom->TargetArmLength = Value;
}

// Called to bind functionality to input
void AMUCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(PlayerInputComponent))
		{
		//Moving
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_MOVE, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Move);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_MOVE, ETriggerEvent::Completed, this, &AMUCharacterPlayer::OnStopMove);

		//Looking
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_LOOK, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Look);

		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_TIMEREWIND, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::TimeWindActivate, true);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_TIMEREWIND, ETriggerEvent::Completed, this, &AMUCharacterPlayer::TimeWindActivate, false);
	}

	SetupGASInputComponent();
}


const FVector2D AMUCharacterPlayer::GetRecentlyMovedVector()
{
	return RecentlyMovedVector;
}

void AMUCharacterPlayer::SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue)
{
	ReleaseMotionWarp(InName);
	
	const FVector PlayerLoc = GetActorLocation();
	const FVector DirVector = FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal();
	const FVector TargetLoc =  PlayerLoc + DirVector * MotionWarpValue;

	
	const FRotator ComponentRot = FollowCamera->GetComponentRotation();
	const FRotator ComponentRotChanged = FRotator(0, ComponentRot.Yaw, 0);

	switch (InMotionWarpType)
	{
	case EMotionWarpType::TranslationAndRotation:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName,  TargetLoc, ComponentRotChanged);
		break;
	case EMotionWarpType::RotationOnly:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName, FVector::ZeroVector, ComponentRotChanged);
		break;
	case EMotionWarpType::TranslationOnly:
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(InName, TargetLoc, FRotator::ZeroRotator);
		break;
	}
}

void AMUCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_SPRINT, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 0);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_SPRINT, ETriggerEvent::Completed, this, &AMUCharacterPlayer::GASInputReleased, 0);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_LMATTACK, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 1);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_DODGE, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 2);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_JUMP, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 3);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_JUMP, ETriggerEvent::Completed, this, &AMUCharacterPlayer::GASInputReleased, 3);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_CHARGE, ETriggerEvent::Completed, this, &AMUCharacterPlayer::GASInputPressed, 4);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_DEFENSE, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 5);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_DEFENSE, ETriggerEvent::Completed, this, &AMUCharacterPlayer::GASInputReleased, 5);
	}
}

void AMUCharacterPlayer::GASInputPressed(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);

	if (Spec)
	{
		Spec->InputPressed = true;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputPressed(*Spec);	
		}
		else
		{
			ASC->TryActivateAbility(Spec->Handle);
		}
	}
}

void AMUCharacterPlayer::GASInputReleased(int32 InputId)
{
	FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputId);

	if (Spec)
	{
		Spec->InputPressed = false;
		if (Spec->IsActive())
		{
			ASC->AbilitySpecInputReleased(*Spec);	
		}
	}
}

void AMUCharacterPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (TimeWindComponent->GetTimeWind())
	{
		return;
	}

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		RecentlyMovedVector = MovementVector;
	}
}

void AMUCharacterPlayer::OnStopMove(const FInputActionValue& Value)
{
	RecentlyMovedVector = FVector2D::Zero();
}

void AMUCharacterPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMUCharacterPlayer::TimeWindActivate(bool InActivationMode)
{
	ITimeWinder* TimeWinder = GetWorld()->GetAuthGameMode<ITimeWinder>();

	if (TimeWinder)
	{
		if (InActivationMode)
		{
			TimeWinder->TimeWindActivate();
			TimelineComponent->Play();
		}
		else
		{
			TimeWinder->TimeWindDeactivate();
			TimelineComponent->Reverse();
		}
	}
}


