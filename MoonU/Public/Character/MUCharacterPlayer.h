// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SpaceTraveler.h"
#include "Interface/Sprinter.h"
#include "Interface/SuitEquipper.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class MOONU_API AMUCharacterPlayer : public ACharacter, public ISuitEquipper, public ISprinter, public ISpaceTraveler, public IGameplayTagWidgetOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterPlayer();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region ISuitEquipper
	virtual FSuitDelegate& GetSuitEquipEvent() override;
	
	virtual FSuitDelegate& GetHeadEquipEvent() override;

	virtual bool GetHeadEquipped() const override;

	virtual bool GetSuitEquipped() const override;
	
	virtual void SetSuitEquipped(bool InSuitEquip) override;
	
	virtual void SetHeadEquipped(bool InSuitEquip) override;
#pragma endregion

#pragma region ISprinter
	virtual void OnSprint() override;

	virtual void OnUnsprint() override;

	virtual bool IsSprinting() const override;
#pragma endregion

#pragma region CacheSkeletalMeshes
	
	UFUNCTION(BlueprintImplementableEvent)
	TArray<USkeletalMeshComponent*> GetHeadMeshComponents_BP();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<USkeletalMeshComponent*> GetSuitBodyMeshComponents_BP();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<USkeletalMeshComponent*> GetNormalBodyMeshComponents_BP();
#pragma endregion 

#pragma region ISpaceTraveler
	virtual void OnCharacterOutBasement() override;
	virtual void OnCharacterInBasement() override;
#pragma endregion

#pragma region IGameplayTagWidgetOwner
	virtual UUserWidget* GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual void ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual void HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual IGameplayTagWidgetOwner* GetGameplayTagWidgetOwner();	
#pragma endregion
	
protected :
	
#pragma region Interaction
	void SphereTraceForInteraction();

	void FilterInteraction(const TArray<FHitResult>& InHitResult);

	void InteractionWidgetBoard();
#pragma endregion
	
#pragma region InputActionEvent
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void Interact(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void UnSprint(const FInputActionValue& Value);
#pragma endregion
	
#pragma region SuitEventBind
	UFUNCTION()
	void SuitChanged(bool bInSuitEquipped);

	UFUNCTION()
	void HeadChanged(bool bInHeadEquipped);
#pragma endregion

	void CacheAllSkeletalMeshes();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UMUSuitComponent> SuitComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCharacterStatusComponent> StatusComponent;
	
	UPROPERTY(Transient, VisibleAnywhere, Category = "Runtime Head Mesh")
	TArray<USkeletalMeshComponent*> HeadMeshComponents;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Runtime Head Mesh")
	TArray<USkeletalMeshComponent*> SuitBodyMeshComponents;
	
	UPROPERTY(Transient, VisibleAnywhere, Category = "Runtime Head Mesh")
	TArray<USkeletalMeshComponent*> NormalBodyMeshComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction | Radius")
	float InteractionRadius = 100.0f;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Interaction | Actor")
	TObjectPtr<AActor> CachedInteractionActor;
	
private : 
	FSuitDelegate SuitEquipDelegate;
	FSuitDelegate HeadEquipDelegate;
};
