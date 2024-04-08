// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MUDefines.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/MUGameSettings.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/Input/MUEnhancedInputComponent.h"
#include "MotionWarpingComponent.h"
#include "Framework/MUPlayerState.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMUCharacterPlayer::AMUCharacterPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");
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

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}
	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		ASC->GiveAbility(StartSpec);
	}
}

// Called to bind functionality to input
void AMUCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_JUMP, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_JUMP, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_MOVE, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Move);

		//Looking
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_LOOK, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Look);
	}

	SetupGASInputComponent();
}

void AMUCharacterPlayer::SetMotionWarp()
{
	const FVector PlayerLoc = GetActorLocation();
	const FVector TargetLoc =  PlayerLoc + GetActorForwardVector() * 5.0f;

	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(COMBO_MOTION_WARP,  TargetLoc);
}

void AMUCharacterPlayer::SetupGASInputComponent()
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(InputComponent);

		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_SPRINT, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 0);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_SPRINT, ETriggerEvent::Completed, this, &AMUCharacterPlayer::GASInputReleased, 0);
		EnhancedInputComponent->BindActionByTag(InputConfig, MU_INPUT_LMATTACK, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::GASInputPressed, 1);
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

UAbilitySystemComponent* AMUCharacterPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

UMUComboActionData* AMUCharacterPlayer::GetComboActionData() const
{
	return ComboActionData;
}

void AMUCharacterPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

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
	}
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


