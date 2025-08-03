// Fill out your copyright notice in the Description page of Project Settings.


#include "Training/PainterCanvasWidget.h"

#include "ImageUtils.h"
#include "NNE.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Data/MUStruct.h"
#include "Engine/Canvas.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Training/CanvasWidget.h"
void UPainterCanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(PaintButton) )
	{
		PaintButton->OnClicked.AddDynamic( this, &UPainterCanvasWidget::OnPaintButtonPressed );
	}

	RenderTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D( this, UCanvasRenderTarget2D::StaticClass(), 256, 256 );
	RenderTarget->OnCanvasRenderTargetUpdate.AddDynamic( this, &UPainterCanvasWidget::DrawToCanvas );
}

int32 UPainterCanvasWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if ( IsValid( RenderTarget ) == true )
	{
		RenderTarget->UpdateResource();	
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UPainterCanvasWidget::OnPaintButtonPressed()
{
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
	
	
	TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
	ModelInstance = Runtime->CreateModel(PreloadedModelData)->CreateModelInstance();
	
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

	AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [&]()
	{	
		if (ModelInstance->RunSync(InputBindings, OutputBindings) != 0)
		{
		UE_LOG(LogTemp, Error, TEXT("Failed to run the model"));
		}
		AsyncTask(ENamedThreads::GameThread, [&]()
		{
			// 해당 사항의 구현화 이유는 백그라운드 스레드를 활용하는 부분이기에, 게임스레드에서 데이터 활용을 위한 부분임.
			for ( auto& Num : OutputData )
			{
				UE_LOG(LogTemp, Log, TEXT("Output : %f"), Num );
			}
		});
	});
	
	if ( IsValid(CanvasWidget) )
	{
		CanvasWidget->ResetAllMember();
	}
}

void UPainterCanvasWidget::DrawToCanvas(UCanvas* Canvas, int32 Width, int32 Height)
{
	if (!IsValid(CanvasWidget))
	{
		return;
	}

	FVector2D CanvasSize = FVector2D(Width, Height);  // 보통 256x256
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	// 배경 박스 (디버깅용)
	Canvas->K2_DrawBox(FVector2D(0, 0), CanvasSize, 0.f, FLinearColor::White);

	for (const FDrawingCoordinate& Coords : CanvasWidget->GetAllCoordinate())
	{
		const TArray<FVector2D>& Coordinate = Coords.Coordinates;

		for (int32 i = 0; i < Coordinate.Num() - 1; ++i)
		{
			FVector2D StartViewport = Coordinate[i];
			FVector2D EndViewport = Coordinate[i + 1];

			// ✅ 뷰포트 → 캔버스 좌표로 정규화
			FVector2D StartCanvas = (StartViewport / ViewportSize) * CanvasSize;
			FVector2D EndCanvas = (EndViewport / ViewportSize) * CanvasSize;

			// 선 그리기
			Canvas->K2_DrawLine(StartCanvas, EndCanvas, 10.f, FLinearColor::White);
		}
	}
}
