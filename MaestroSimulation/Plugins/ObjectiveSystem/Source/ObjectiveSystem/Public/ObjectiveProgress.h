#pragma once

#include "CoreMinimal.h"
#include "ObjectiveBase.h"
#include "ObjectiveProgress.generated.h"

/**
 * Objective that tracks a numeric value (Current / Target).
 */
UCLASS(Blueprintable)
class OBJECTIVESYSTEM_API UObjectiveProgress : public UObjectiveBase
{
	GENERATED_BODY()

public:
	// The specific tag this objective listens for (e.g., "Picked_up_tool")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FName TargetEventTag;

	// How many do we need?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	int32 TargetAmount = 10;

	// Current progress
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	int32 CurrentAmount = 0;

	// -- Overrides --

	virtual void ActivateObjective(UObject* WorldContextObject) override;
	virtual void OnExternalEvent_Implementation(FName EventTag, int32 Value) override;
	virtual FText GetProgressText_Implementation() override;
};