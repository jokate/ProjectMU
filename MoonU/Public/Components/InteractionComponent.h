// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Interactor.h"
#include "InteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UInteractionComponent : public UActorComponent, public IInteractor
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();
	
#pragma region IInteractor
	virtual void TryInteract() override;

	virtual void SetCachedInteractionTarget(AActor* TargetActor) override;
#pragma endregion IInteractor

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> CachedActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UGameplayAbility> RelatedAbility;
};
