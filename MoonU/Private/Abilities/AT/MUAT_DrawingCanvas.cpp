// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_DrawingCanvas.h"

#include "ImageUtils.h"
#include "NNE.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Training/PainterCanvasWidget.h"

UMUAT_DrawingCanvas* UMUAT_DrawingCanvas::CreateDrawingCanvas(UGameplayAbility* GameplayAbility,
                                                              UNNEModelData* ModelData, FGameplayTag InWidgetTag )
{
	UMUAT_DrawingCanvas* DrawingCanvas = NewAbilityTask<UMUAT_DrawingCanvas>(GameplayAbility);
	DrawingCanvas->PreloadedModelData = ModelData;
	DrawingCanvas->WidgetTag = InWidgetTag;

	return DrawingCanvas;
}

void UMUAT_DrawingCanvas::Activate()
{
	Super::Activate();

	UPainterCanvasWidget* CanvasWidget = Cast<UPainterCanvasWidget>(TagWidget);

	if ( IsValid( CanvasWidget ) == true )
	{
		CanvasWidget->OnCanvasButtonPressed.AddDynamic( this, &UMUAT_DrawingCanvas::ProcessModelRun );
	}
}

void UMUAT_DrawingCanvas::OnDestroy(bool bInOwnerFinished)
{
	UPainterCanvasWidget* CanvasWidget = Cast<UPainterCanvasWidget>(TagWidget);

	if ( IsValid( CanvasWidget ) == true )
	{
		CanvasWidget->OnCanvasButtonPressed.RemoveAll( this );
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_DrawingCanvas::ProcessModelRun()
{
	ProcessData();
	RunModel();
}

void UMUAT_DrawingCanvas::ProcessData()
{
	UPainterCanvasWidget* CanvasWidget = Cast<UPainterCanvasWidget>(TagWidget);

	if ( IsValid( CanvasWidget ) == false )
	{
		return;
	}

	UCanvasRenderTarget2D* RenderTarget = CanvasWidget->GetRenderTarget();
	
	FTextureRenderTargetResource* RTResource = RenderTarget->GameThread_GetRenderTargetResource();

	TArray<FColor> OutBMP;
	RTResource->ReadPixels(OutBMP);
	
	FIntPoint DestSize(RTResource->GetSizeX(), RTResource->GetSizeY());

	TArray64<uint8> CompressedPNG;
	FImageUtils::PNGCompressImageArray(DestSize.X, DestSize.Y, OutBMP, CompressedPNG);
	
	FString FilePath = FPaths::ProjectSavedDir() / TEXT("Pattern/NormalizedPat.png");
	FFileHelper::SaveArrayToFile(CompressedPNG, *FilePath);
	
	TArray<FColor> Pixels;
	if (RTResource != nullptr ) 
	{
		RTResource->ReadPixels(Pixels);
	}
	// CHW 순서: [R, G, B], mean=0.5, std=0.5 → (x / 127.5) - 1.0
	InputData.SetNum(256 * 256 * 3);

	int32 PixelIndex = 0;
	for (int32 Y = 0; Y < 256; ++Y)
	{
		for (int32 X = 0; X < 256; ++X)
		{
			const FColor& Pixel = Pixels[PixelIndex++];
			int32 BaseIndex = Y * 256 + X;

			// C=0: R
			InputData[0 * 256 * 256 + BaseIndex] = (Pixel.R / 127.5f) - 1.0f;
			// C=1: G
			InputData[1 * 256 * 256 + BaseIndex] = (Pixel.G / 127.5f) - 1.0f;
			// C=2: B
			InputData[2 * 256 * 256 + BaseIndex] = (Pixel.B / 127.5f) - 1.0f;
		}
	}
}

void UMUAT_DrawingCanvas::RunModel()
{
	// 런타임 생성.
	TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));

	if ( Runtime == nullptr )
	{
		return;
	}

	// 모델에는 유일 참조 보장.
	TUniquePtr<UE::NNE::IModelCPU> Model = Runtime->CreateModel(PreloadedModelData.Get());

	if ( Model == nullptr )
	{
		return;
	}
	
	ModelInstance = Model->CreateModelInstance();

	if ( ModelInstance == nullptr )
	{
		return;
	}
	
	TConstArrayView<UE::NNE::FTensorDesc> InputTensorDescs = ModelInstance->GetInputTensorDescs();
	
	UE::NNE::FSymbolicTensorShape SymbolicInputTensorShape = InputTensorDescs[0].GetShape();
	
	TArray<UE::NNE::FTensorShape> InputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicInputTensorShape) };
 
	ModelInstance->SetInputTensorShapes(InputTensorShapes);
 
	TConstArrayView<UE::NNE::FTensorDesc> OutputTensorDescs = ModelInstance->GetOutputTensorDescs();
	UE::NNE::FSymbolicTensorShape SymbolicOutputTensorShape = OutputTensorDescs[0].GetShape();
	TArray<UE::NNE::FTensorShape> OutputTensorShapes = { UE::NNE::FTensorShape::MakeFromSymbolic(SymbolicOutputTensorShape) };
	
	InputBindings.SetNumZeroed(1);
	InputBindings[0].Data = InputData.GetData();
	InputBindings[0].SizeInBytes = InputData.Num() * sizeof(float);

	OutputData.SetNumZeroed(OutputTensorShapes[0].Volume());
	OutputBindings.SetNumZeroed(1);
	OutputBindings[0].Data = OutputData.GetData();
	OutputBindings[0].SizeInBytes = OutputData.Num() * sizeof(float);

	// 쿼리 자체는 백그라운드에서 싱행하는 것이 좋음. 따라서 관련 부분에 대해서 타 스레드에 위임하는 방식
	AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [&]()
	{	
		if (ModelInstance->RunSync(InputBindings, OutputBindings) != 0)
		{
		UE_LOG(LogTemp, Error, TEXT("Failed to run the model"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Running Model"));
		}
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			// 해당 사항의 구현화 이유는 백그라운드 스레드를 활용하는 부분이기에, 게임스레드에서 데이터 활용을 위한 부분임.
			// 결과 확보.
			for ( auto& Num : OutputData )
			{
				UE_LOG(LogTemp, Log, TEXT("Output : %f"), Num );
			}
			if ( OnCanvasDrawingComplete.IsBound() )
			{
				OnCanvasDrawingComplete.Broadcast( OutputData );	
			}
		});
	});
}
