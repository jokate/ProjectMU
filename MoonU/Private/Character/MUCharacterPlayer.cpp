// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MUDefines.h"
#include "Camera/CameraComponent.h"
#include "Components/CharacterStatusComponent.h"
#include "Components/MUSuitComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/MUGameSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/HUD.h"
#include "Interface/InteractableTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Blueprint/UserWidget.h"
#include "Components/CraftComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/Input/MUEnhancedInputComponent.h"
#include "Interface/UI/Widget/MUWidgetInterface.h"

// Sets default values
AMUCharacterPlayer::AMUCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SuitComponent = CreateDefaultSubobject<UMUSuitComponent>("Suit Component");
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>("StatusComponent");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	CraftComponent = CreateDefaultSubobject<UCraftComponent>("CraftComponent");
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMUCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	const auto* GS = UMUGameSettings::Get();
	SuitEquipDelegate.BindUObject(this, &AMUCharacterPlayer::SuitChanged);
	HeadEquipDelegate.BindUObject(this, &AMUCharacterPlayer::HeadChanged);
	
	CacheAllSkeletalMeshes();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	UnEquipSuit();

	if (auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner())
	{
		GameplayTagWidgetOwner->ShowWidgetByGameplayTag(GS->HUDGameplayTag);
	}
}

void AMUCharacterPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SuitEquipDelegate.Unbind();
	HeadEquipDelegate.Unbind();
	
	Super::EndPlay(EndPlayReason);
}

void AMUCharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsLocallyControlled())
	{
		SphereTraceForInteraction();
		InteractionWidgetBoard();
	}
}

// Called to bind functionality to input
void AMUCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	const auto* GS = UMUGameSettings::Get();
	if (GS == nullptr)
	{
		return;
	}
	// Set up action bindings
	if (UMUEnhancedInputComponent* EnhancedInputComponent = CastChecked<UMUEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->JumpInputTag, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->JumpInputTag, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->MoveInputTag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Move);

		//Looking
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->LookInputTag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Look);

		EnhancedInputComponent->BindActionByTag(InputConfig, GS->InteractInputTag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Interact);
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->SprintInputTag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::Sprint);
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->SprintInputTag, ETriggerEvent::Completed, this, &AMUCharacterPlayer::UnSprint);
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->InventoryUITag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::UIInputAction);
		EnhancedInputComponent->BindActionByTag(InputConfig, GS->UICloseTag, ETriggerEvent::Triggered, this, &AMUCharacterPlayer::CloseUI);
	}

}

FSuitDelegate& AMUCharacterPlayer::GetSuitEquipEvent()
{
	return SuitEquipDelegate;
}

bool AMUCharacterPlayer::GetSuitEquipped() const
{
	return SuitComponent->GetSuitEquipped();
}

void AMUCharacterPlayer::EquipSuit(AActor* SuitEntity)
{
	SuitComponent->EquipSuit(SuitEntity);
}

void AMUCharacterPlayer::UnEquipSuit()
{
	SuitComponent->UnEquipSuit();
}

void AMUCharacterPlayer::OnSprint()
{
	auto* CharacterMove = GetCharacterMovement();
	if (CharacterMove != nullptr)
	{
		CharacterMove->MaxWalkSpeed = SPRINT_SPEED;
	}

	StatusComponent->OnSprint();	
}

void AMUCharacterPlayer::OnUnsprint()
{
	auto* CharacterMove = GetCharacterMovement();
	if (CharacterMove != nullptr)
	{
		CharacterMove->MaxWalkSpeed = WALK_SPEED;
	}

	StatusComponent->OnUnsprint();
}

bool AMUCharacterPlayer::IsSprinting() const
{
	const auto* CharacterMove = GetCharacterMovement();
	if (CharacterMove == nullptr)
	{
		return false;		
	}

	const FVector MoveVector2D = CharacterMove->Velocity * FVector(1.0f, 1.0f, 0.0f);

	return !MoveVector2D.IsNearlyZero();
}

void AMUCharacterPlayer::SphereTraceForInteraction()
{
	CachedInteractionActor = nullptr;
	
	//반경에 따른 탐색을 지정한다.
	const FVector StartPoint = GetCharacterMovement()->GetActorFeetLocation();
	const FVector EndPoint = StartPoint + FVector::UpVector;
	TArray<FHitResult> OutHitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes
	{
		UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1)
	};
	
	UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		this,
		StartPoint,
		EndPoint,
		InteractionRadius
		, ObjectTypes
		, false
		, TArray<AActor*>()
		, EDrawDebugTrace::None
		, OutHitResult
		, true
		);
	
	if (OutHitResult.Num() == 0)
	{
		return;
	}

	FilterInteraction(OutHitResult);
}

void AMUCharacterPlayer::FilterInteraction(const TArray<FHitResult>& InHitResult)
{
	// Line Cast를 통해서 조절을 해줘야 한다고 생각.
	AController* PController = GetController();
	if (PController == nullptr)
	{
		return;
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(PController);
	if (PlayerController == nullptr)
	{
		return;
	}
	FVector StartLocation;
	FRotator Direction;
	GetActorEyesViewPoint(StartLocation, Direction);
	FVector DirectionVector = UKismetMathLibrary::GetForwardVector(Direction);
	FVector EndLocation = StartLocation + DirectionVector * InteractionRadius * 2;
	
	FHitResult OutHitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes
	{
		UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1)
	};
	
	UKismetSystemLibrary::LineTraceSingleForObjects
	(
		this,
		StartLocation,
		EndLocation,
		ObjectTypes,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		OutHitResult,
		true
	);
	
	AActor* LineHitActor = OutHitResult.GetActor();
	if (LineHitActor == nullptr)
	{
		return;
	}
	
	for (const FHitResult& HitResult : InHitResult)
	{
		const AActor* HitActor = HitResult.GetActor();

		if (HitActor == nullptr)
		{
			continue;
		}
		
		if (LineHitActor != HitActor)
		{
			continue;
		}
		auto* InteractableTarget = Cast<IInteractableTarget>(LineHitActor);
		if (InteractableTarget == nullptr)
		{
			continue;
		}

		if (InteractableTarget->IsInteractable(this))
		{
			CachedInteractionActor = LineHitActor;
			break;
		}
	}
}

void AMUCharacterPlayer::InteractionWidgetBoard()
{
	const auto* GS = UMUGameSettings::Get();

	if (GS == nullptr)
	{
		return;
	}
	
	if (auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner())
	{
		auto* Widget = GameplayTagWidgetOwner->GetWidgetByGameplayTag(GS->HUDGameplayTag);

		if (Widget == nullptr)
		{
			return;		
		}

		if (auto* HUDWidget = Cast<IMUWidgetInterface>(Widget))
		{
			HUDWidget->OnWidgetUpdatedByActor(CachedInteractionActor);
		}
	}
}

void AMUCharacterPlayer::OnCharacterOutBasement()
{
	SuitComponent->OnCharacterOutBasement();
}

void AMUCharacterPlayer::OnCharacterInBasement()
{
	SuitComponent->OnCharacterInBasement();
}

UUserWidget* AMUCharacterPlayer::GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return nullptr;
	}

	return GameplayTagWidgetOwner->GetWidgetByGameplayTag(InGameplayTag);
}

void AMUCharacterPlayer::ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return;
	}

	GameplayTagWidgetOwner->ShowWidgetByGameplayTag(InGameplayTag);
}

void AMUCharacterPlayer::HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return;
	}

	GameplayTagWidgetOwner->HideWidgetByGameplayTag(InGameplayTag);
}

IGameplayTagWidgetOwner* AMUCharacterPlayer::GetGameplayTagWidgetOwner()
{
	if (IsLocallyControlled() == false)
	{
		return nullptr;
	}

	auto* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == nullptr)
	{
		return nullptr;
	}

	auto* HUD = PlayerController->GetHUD();
	
	if (HUD == nullptr)
	{
		return nullptr;	
	}

	auto* GameplayTagWidgetOwner = Cast<IGameplayTagWidgetOwner>(HUD);

	if (GameplayTagWidgetOwner == nullptr)
	{
		return nullptr;
	}
	
	return GameplayTagWidgetOwner;
}

bool AMUCharacterPlayer::IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag)
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return false;
	}

	return GameplayTagWidgetOwner->IsWidgetByGameplayTagInViewport(InGameplayTag);
}

bool AMUCharacterPlayer::IsGameplayWidgetInViewport()
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return false;
	}

	return GameplayTagWidgetOwner->IsGameplayWidgetInViewport();
}

void AMUCharacterPlayer::HideAllWidgetForGameplay()
{
	auto* GameplayTagWidgetOwner = GetGameplayTagWidgetOwner();

	if (GameplayTagWidgetOwner == nullptr)
	{
		return;
	}

	GameplayTagWidgetOwner->HideAllWidgetForGameplay();
}

void AMUCharacterPlayer::OwnInventory(const FInventoryData& Item)
{
	InventoryComponent->OwnInventory(Item);
}

void AMUCharacterPlayer::DisOwnInventory(const FInventoryData& Item)
{
	InventoryComponent->DisOwnInventory(Item);
}

void AMUCharacterPlayer::OwnInventoryByIndex(const FInventoryData& Item, int32 Index)
{
	InventoryComponent->OwnInventoryByIndex(Item, Index);
}

void AMUCharacterPlayer::DisownInventoryByIndex(int32 Index)
{
	InventoryComponent->DisownInventoryByIndex(Index);
}

int32 AMUCharacterPlayer::GetMaxStorageAmount() const
{
	return InventoryComponent->GetMaxStorageAmount();
}

const TArray<FInventoryData>& AMUCharacterPlayer::GetTotalInventoryData()
{
	return InventoryComponent->GetTotalInventoryData();
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

void AMUCharacterPlayer::Interact(const FInputActionValue& Value)
{
	if (CachedInteractionActor == nullptr)
	{
		return;
	}

	if (IsGameplayWidgetInViewport())
	{
		return;
	}

	if (auto* InteractableTarget = Cast<IInteractableTarget>(CachedInteractionActor))
	{
		InteractableTarget->OnInteracted(this);
	}
}

void AMUCharacterPlayer::Sprint(const FInputActionValue& Value)
{
	OnSprint();
}

void AMUCharacterPlayer::UnSprint(const FInputActionValue& Value)
{
	OnUnsprint();
}

void AMUCharacterPlayer::UIInputAction(const FInputActionInstance& ActionData)
{
	if (auto* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(InputComponent))
	{
		const FGameplayTag& GameplayTag = EnhancedInputComponent->GetGameplayTagByInputAction(ActionData.GetSourceAction());

		if (IsWidgetByGameplayTagInViewport(GameplayTag))
		{
			HideWidgetByGameplayTag(GameplayTag);
		}
		else
		{
			ShowWidgetByGameplayTag(GameplayTag);
		}
	}
}

void AMUCharacterPlayer::CloseUI()
{
	HideAllWidgetForGameplay();
}

void AMUCharacterPlayer::SuitChanged(bool bInSuitEquipped)
{
	for (auto* SuitBodyMeshComponent : SuitBodyMeshComponents)
	{
		SuitBodyMeshComponent->SetHiddenInGame(!bInSuitEquipped);
		SuitBodyMeshComponent->SetCastShadow(bInSuitEquipped);
	}

	for (auto* NormalBodyMeshComponent : NormalBodyMeshComponents)
	{
		NormalBodyMeshComponent->SetHiddenInGame(bInSuitEquipped);
		NormalBodyMeshComponent->SetCastShadow(!bInSuitEquipped);
	}
}

void AMUCharacterPlayer::HeadChanged(bool bInHeadEquipped)
{
	for (auto* HeadMeshComponent : HeadMeshComponents)
	{
		HeadMeshComponent->SetHiddenInGame(!bInHeadEquipped);
		HeadMeshComponent->SetCastShadow(bInHeadEquipped);
	}
}

void AMUCharacterPlayer::CacheAllSkeletalMeshes()
{
	SuitBodyMeshComponents = GetSuitBodyMeshComponents_BP();
	HeadMeshComponents = GetHeadMeshComponents_BP();
	NormalBodyMeshComponents = GetNormalBodyMeshComponents_BP();
}

