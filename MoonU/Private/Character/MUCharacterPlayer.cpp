// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MUDefines.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/Input/MUEnhancedInputComponent.h"
#include "MotionWarpingComponent.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Components/AbilityInitComponent.h"
#include "Components/EnforcementComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/MULevelUpComponent.h"
#include "Components/WorldPartitionStreamingSourceComponent.h"
#include "Data/DataTable/MUData.h"
#include "GameFramework/GameModeBase.h"
#include "Indicator/MUIndicatorManageSubsystem.h"
#include "Interface/StageManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/MUFunctionLibrary.h"
#include "Singleton/MUEnforcementSubsystem.h"
#include "Singleton/MUWidgetDelegateSubsystem.h"

// Sets default values
AMUCharacterPlayer::AMUCharacterPlayer(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
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

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	EnforcementComponent = CreateDefaultSubobject<UEnforcementComponent>("EnforcementComponent");

	StreamingComponent = CreateDefaultSubobject<UWorldPartitionStreamingSourceComponent>("StreamingComponent");
}

// Called when the game starts or when spawned
void AMUCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetupInputByID(COMMON_CHARACTER_INPUT);
	SetupInputByID(CharacterID);
	
	StreamingComponent->EnableStreamingSource();

	RegisterLocalStage();
	RegisterEnforcementEvent();
}

void AMUCharacterPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(AbilityInitComponent ) == true)
	{
		AbilityInitComponent->OnEndPlay(CharacterID);	
	}

	LevelUpComponent->OnLevelUpEventCallback.RemoveAll(this);

	StreamingComponent->DisableStreamingSource();
	
  	Super::EndPlay(EndPlayReason);
}

ETeamAttitude::Type AMUCharacterPlayer::GetTeamAttitudeTowards(const AActor& Other) const
{
	return ETeamAttitude::Hostile;
}

void AMUCharacterPlayer::SetupInputByID(int32 InputID)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		FMUInputMapper InputMapper;
		if (UMUFunctionLibrary::GetInputMapperData(this, InputID, InputMapper) == false)
		{
			return;
		}

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapper.InputMappingContext, InputMapper.Priority);
		}
	}
}

bool AMUCharacterPlayer::IsSkillActive()
{
	// input is a Vector2D
	APlayerController* PC = GetController<APlayerController>();
	if ( IsValid( PC ) == false )
	{
		return false;
	}
	
	bool bIsActive = false;
	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PC->GetLocalPlayer()))
	{
		bIsActive = Subsystem->IsSkillActive();
	}

	return bIsActive;
}

// Called to bind functionality to input
void AMUCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	SetupDefaultInput(PlayerInputComponent);
	SetupGASInputComponent(CharacterID);
}

void AMUCharacterPlayer::SetupDefaultInput(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(PlayerInputComponent))
	{
		FMUInputMapper InputMapper;
		if (UMUFunctionLibrary::GetInputMapperData(this, COMMON_CHARACTER_INPUT, InputMapper) == false)
		{
			return;
		}

		//Moving
		EnhancedInputComponent->BindActionByTag(InputMapper.InputConfig, MU_INPUT_MOVE, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Move);
		EnhancedInputComponent->BindActionByTag(InputMapper.InputConfig, MU_INPUT_MOVE, ETriggerEvent::Completed, this, &AMUCharacterPlayer::OnStopMove);

		//Looking
		EnhancedInputComponent->BindActionByTag(InputMapper.InputConfig, MU_INPUT_LOOK, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Look);
	}

	SetupGASInputComponent(COMMON_CHARACTER_INPUT);
}

void AMUCharacterPlayer::SetupSkillInput(int32 InputID)
{
	
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

int32 AMUCharacterPlayer::GetContinuousEnforcementLevel()
{
	if (IsValid(LevelUpComponent) == true)
	{
		return LevelUpComponent->GetContinuousEnforcementLevel();
	}

	return 0;
}

bool AMUCharacterPlayer::GetEnforcementIDs(TArray<int32>& OutEnforcementIDs)
{
	if ( IsValid(EnforcementComponent) == false)
	{
		return false;
	}

	OutEnforcementIDs = EnforcementComponent->GetEnforcementIDs();
	
	return true;
}

void AMUCharacterPlayer::SetupCanLook( bool bInCanLook )
{
	APlayerController* PC = GetController<APlayerController>();

	if ( IsValid(PC) == true )
	{
		PC->SetIgnoreLookInput( bInCanLook );
		bUseControllerRotationYaw = !bInCanLook;
	}
}

void AMUCharacterPlayer::SetupGASInputComponent( int32 InputID )
{
	if (IsValid(ASC) && IsValid(InputComponent))
	{
		UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(InputComponent);

		if ( IsValid(EnhancedInputComponent) == false)
		{
			return;
		}
		
		FMUInputMapper InputMapper;
		if (UMUFunctionLibrary::GetInputMapperData(this, InputID, InputMapper) == false)
		{
			return;
		}

		for ( FTagByInput& InputByTag : InputMapper.InputByTags )
		{
			FGameplayAbilitySpec StartSpec(InputByTag.InputAbility);
			StartSpec.InputID = InputByTag.InputID;
			ASC->GiveAbility(StartSpec);
			
			UMUFunctionLibrary::BindInputActionByTag(this, InputID, InputByTag);
		}
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

void AMUCharacterPlayer::RegisterLocalStage()
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	if ( IsValid(GameMode) == false )
	{
		return;
	}
	
	IStageManager* StageManager = Cast<IStageManager>(GameMode);

	if ( StageManager == nullptr )
	{
		return;
	}

	StageManager->RegisterOwnerActor( this );
}

void AMUCharacterPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMEWINDING))
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
	if ( IsSkillActive() == true )
	{
		return;
	} 
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if ( Controller != nullptr )
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMUCharacterPlayer::AddItem(int32 ItemId, int32 ItemAmount)
{
	InventoryComponent->AddItem(ItemId, ItemAmount);
}

void AMUCharacterPlayer::UseItemBySlot(int32 SlotIndex)
{
	InventoryComponent->UseItemBySlot(SlotIndex);
}

void AMUCharacterPlayer::UseItemByItemID(int32 SlotIndex)
{
	InventoryComponent->UseItemByItemID(SlotIndex);
}

void AMUCharacterPlayer::TryInteract()
{
	InteractionComponent->TryInteract();
}

void AMUCharacterPlayer::SetCachedInteractionTarget(AActor* TargetActor)
{
	InteractionComponent->SetCachedInteractionTarget(TargetActor);
}

void AMUCharacterPlayer::TriggerInputSkill(ESkillSlotType SkillSlot)
{
	if ( IsValid(EnforcementComponent) == true )
	{
		EnforcementComponent->TriggerInputSkill( SkillSlot );
	}
}

void AMUCharacterPlayer::AddSkillSlot(ESkillSlotType SkillSlotType, FName SkillID)
{
	if ( IsValid( EnforcementComponent ) == true )
	{
		EnforcementComponent->AddSkillSlot(SkillSlotType, SkillID);
	}
}

void AMUCharacterPlayer::RemoveSkillSlot(ESkillSlotType SkillSlotType)
{
	if ( IsValid(EnforcementComponent ) == true )
	{
		EnforcementComponent->RemoveSkillSlot(SkillSlotType);
	} 
}

const FName AMUCharacterPlayer::GetSkillIDBySlot(ESkillSlotType SkillSlot)
{
	if ( IsValid(EnforcementComponent) == true )
	{
		return EnforcementComponent->GetSkillIDBySlot(SkillSlot);
	}

	return FName();
}

void AMUCharacterPlayer::RegisterEnforcementEvent()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UMUEnforcementSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUEnforcementSubsystem>(PlayerController->GetLocalPlayer());
		if ( !IsValid(Subsystem))
        {
        	return;
        }

		Subsystem->OnCharacterAttributeAdded.AddDynamic( this, &AMUCharacterPlayer::OnAttributeEnforcementAdded );
		Subsystem->OnCharacterSkillAdded.AddDynamic( this, &AMUCharacterPlayer::OnSkillEnforcementAdded );
	}
}

void AMUCharacterPlayer::OnAttributeEnforcementAdded(const int32 InCharacterID, 
	const int32 EnforcementID)
{
	if ( CharacterID != InCharacterID || !IsValid(EnforcementComponent))
	{
		return;
	}
	
	EnforcementComponent->EnforceAttribute(EnforcementID);
}

void AMUCharacterPlayer::OnSkillEnforcementAdded(const int32 InCharacterID, ESkillSlotType SkillSlotType,
	const int32 EnforcementID)
{
	if ( CharacterID != InCharacterID || !IsValid(EnforcementComponent))
	{
		return;
	}

	EnforcementComponent->EnforceSkill( SkillSlotType, EnforcementID );
}

void AMUCharacterPlayer::LevelUp()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UMUEnforcementSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUEnforcementSubsystem>(PlayerController->GetLocalPlayer());
		if ( !IsValid(Subsystem))
		{
			return;
		}

		Subsystem->OnPlayerLevelUp();
	}
}

void AMUCharacterPlayer::ResetContinuousEnforcementLevel()
{
	if (IsValid(LevelUpComponent) == true )
	{
		LevelUpComponent->SetContinuousEnforcementLevel( 0 );
	}
}
