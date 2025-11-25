
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "URTReader.generated.h"

class UTextureRenderTarget2D;

UCLASS()
class MAESTROSIMULATION_API URTReader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "RTReader")
	static float GetRTFillPercent(UTextureRenderTarget2D* RT);

private:
	static void SendErrorMessage(const FString& Message);
};
