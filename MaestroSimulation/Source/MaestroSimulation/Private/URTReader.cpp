
#include "URTReader.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Async/ParallelFor.h"
#include <atomic>

float URTReader::GetRTFillPercent(UTextureRenderTarget2D* RT)
{
	if (!RT)
	{
		SendErrorMessage("URTReader: Missing RenderTarget input");
		return 0.0f;
	}

	FRenderTarget* RenderTarget = RT->GameThread_GetRenderTargetResource();
	if (!RenderTarget)
	{
		SendErrorMessage("URTReader: Unable to extract RenderTargetResource");
		return 0.0f;
	}

	TArray<FColor> PixelData;
	RenderTarget->ReadPixels(PixelData);

	int32 TotalPixels = PixelData.Num();
	if (TotalPixels == 0)
	{
		SendErrorMessage("URTReader: No pixels extracted");
		return 0.0f;
	}

	const FColor* DataPtr = PixelData.GetData();
	std::atomic<int32> FilledPixels(0);

	ParallelFor(TotalPixels, [DataPtr, &FilledPixels](int32 Idx)
	{
		if (DataPtr[Idx].R > 0)
		{
			FilledPixels += 1;
		}
	});
	
	return (float)FilledPixels / (float)TotalPixels;
}

void URTReader::SendErrorMessage(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message)
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
	}
}
