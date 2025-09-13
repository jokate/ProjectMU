// Fill out your copyright notice in the Description page of Project Settings.


#include "NNE/MUNNETestPawn.h"

#include "NNE.h"
#include "NNEModelData.h"
#include "NNERuntimeCPU.h"


// Sets default values
AMUNNETestPawn::AMUNNETestPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMUNNETestPawn::BeginPlay()
{
	Super::BeginPlay();
	/*TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
	ModelInstance = Runtime->CreateModel(PreloadedModelData)->CreateModelInstance();
	
	TConstArrayView<UE::NNE::FTensorDesc> InputTensorDescs = ModelInstance->GetInputTensorDescs();
	
	UE::NNE::FSymbolicTensorShape SymbolicInputTensorShape = InputTensorDescs[0].GetShape();
	
	TArray<UE::NNE::FTensorShape> InputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicInputTensorShape) };
 
	ModelInstance->SetInputTensorShapes(InputTensorShapes);
 
	TConstArrayView<UE::NNE::FTensorDesc> OutputTensorDescs = ModelInstance->GetOutputTensorDescs();
	UE::NNE::FSymbolicTensorShape SymbolicOutputTensorShape = OutputTensorDescs[0].GetShape();
	TArray<UE::NNE::FTensorShape> OutputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicOutputTensorShape) };


	// Example for creating in- and outputs
	InputData.SetNumZeroed(InputTensorShapes[0].Volume());
	InputBindings.SetNumZeroed(1);
	InputBindings[0].Data = InputData.GetData();
	InputBindings[0].SizeInBytes = InputData.Num() * sizeof(float);
 
	OutputData.SetNumZeroed(OutputTensorShapes[0].Volume());
	OutputBindings.SetNumZeroed(1);
	OutputBindings[0].Data = OutputData.GetData();
	OutputBindings[0].SizeInBytes = OutputData.Num() * sizeof(float);*/
}

// Called every frame
void AMUNNETestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	if ( !bIsRunning )
	{
		bIsRunning = true;

		for ( auto& Num : OutputData )
		{
			UE_LOG(LogTemp, Log, TEXT("Output : %f"), Num );
		}
		AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [&]()
		{	
		if (ModelInstance->RunSync(InputBindings, OutputBindings) != 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to run the model"));
		}
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			bIsRunning = false;
		});
	});
	}*/
}

// Called to bind functionality to input
void AMUNNETestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

