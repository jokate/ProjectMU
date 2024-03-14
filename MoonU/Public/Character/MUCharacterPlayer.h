// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "Interface/InventoryOwner.h"
#include "Interface/SpaceTraveler.h"
#include "Interface/Sprinter.h"
#include "Interface/SuitEquipper.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "MUCharacterPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class MOONU_API AMUCharacterPlayer : public ACharacter, public ISuitEquipper, public ISprinter, public ISpaceTraveler, public IGameplayTagWidgetOwner
									,public IInventoryOwner
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

	virtual bool GetSuitEquipped() const override;
	
	virtual void EquipSuit(AActor* SuitEntity) override;

	virtual void UnEquipSuit() override;
#pragma endregion

#pragma region ISprinter
	virtual void OnSprint() override;

	virtual void OnUnsprint() override;

	virtual bool IsSprinting() const override;
#pragma endregion

#pragma region CacheSkeletalMesh

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
	
	virtual bool IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag) override;

	virtual bool IsGameplayWidgetInViewport() override;

	virtual void HideAllWidgetForGameplay() override;
#pragma endregion

#pragma region IInventoryOwner
	virtual void OwnInventory(const FInventoryData& Item) override;

	virtual void DisOwnInventory(const FInventoryData& Item) override;

	virtual void OwnInventoryByIndex(const FInventoryData& Item, int32 Index) override;

	virtual void DisownInventoryByIndex(int32 Index) override;

	virtual int32 GetMaxStorageAmount() const override;
	
	virtual const TArray<FInventoryData>& GetTotalInventoryData() override;
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

	void UIInputAction(const FInputActionInstance& ActionData);

	void CloseUI();

#pragma endregion
	
#pragma region SuitEventBind
	UFUNCTION()
	void SuitChanged(bool bInSuitEquipped);
#pragma endregion

	void CacheAllSkeletalMeshes();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input | Config")
	TObjectPtr<class UInputConfig> InputConfig;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UMUSuitComponent> SuitComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCharacterStatusComponent>	 StatusComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UCraftComponent> CraftComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UInventoryComponent> InventoryComponent;

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
};
