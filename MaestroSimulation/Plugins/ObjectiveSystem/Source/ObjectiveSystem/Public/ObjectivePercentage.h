#pragma once

#include "CoreMinimal.h"
#include "ObjectiveBase.h"
#include "ObjectivePercentage.generated.h"

/**
 * Objective for continuous progress (Painting a wall, holding a button).
 * Works with values from 0.0 to 1.0 (0% to 100%).
 */
UCLASS(Blueprintable)
class OBJECTIVESYSTEM_API UObjectivePercentage : public UObjectiveBase
{
	GENERATED_BODY()

public:
	// The tag to listen for (e.g. "CanvasPaint")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FName TargetEventTag;

	// The percent we need (e.g. 95%)?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta=(ClampMin="0.0", ClampMax="1.0"))
	float TargetPercentage = 1.0f;

	// If true, the incoming value is added to current. 
	// If false, the incoming value REPLACES current (Absolute).
	// For a canvas, usually 'false' is better - it just says ("60% done")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bAccumulateValues = false;

	// Current Progress (0.0 - 1.0)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float CurrentPercentage = 0.0f;

	// -- Overrides --
	virtual void ActivateObjective(UObject* WorldContextObject) override;
	virtual void OnExternalEvent_Implementation(FName EventTag, float Value) override;
	virtual FText GetProgressText_Implementation() override;
};