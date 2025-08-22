// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NNERuntimeCPU.h"
#include "GameFramework/Pawn.h"
#include "MUNNETestPawn.generated.h"

class UNNEModelData;

UCLASS()
class MOONU_API AMUNNETestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMUNNETestPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 테스트 폰.
public :
	UPROPERTY( EditAnywhere )
	TObjectPtr<UNNEModelData> PreloadedModelData;

private :
// 	https://dev.epicgames.com/community/learning/courses/e7w/unreal-engine-neural-network-engine-nne/34q9/unreal-engine-nne-quick-start-guide-5-3
	TUniquePtr<UE::NNE::IModelInstanceCPU> ModelInstance;
	TArray<float> InputData;
	TArray<float> OutputData;
	TArray<UE::NNE::FTensorBindingCPU> InputBindings;
	TArray<UE::NNE::FTensorBindingCPU> OutputBindings;
	bool bIsRunning = false;
};
