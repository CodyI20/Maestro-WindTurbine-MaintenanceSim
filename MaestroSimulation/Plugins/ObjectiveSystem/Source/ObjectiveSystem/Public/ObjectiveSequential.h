#pragma once

#include "CoreMinimal.h"
#include "ObjectiveBase.h"
#include "ObjectiveSequential.generated.h"

/**
 * Executes a list of objectives one by one.
 * The Sequence is complete only when all sub-objectives are complete.
 */
UCLASS(Blueprintable)
class OBJECTIVESYSTEM_API UObjectiveSequential : public UObjectiveBase
{
	GENERATED_BODY()

public:
	// The list of steps to perform.
	// EditInlineNew allows the creation of specific logic for each step right inside this list.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Config")
	TArray<UObjectiveBase*> Objectives;

	// Track which step we are on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	int32 CurrentStepIndex = 0;

	// -- Overrides --

	virtual void ActivateObjective(UObject* WorldContextObject) override;
    
	// Override these to forward the events to the *active* sub-objective only
	virtual void OnExternalEvent_Implementation(FName EventTag, int32 Value) override;
	virtual void OnExternalProgress_Implementation(FName EventTag, float Value) override;
	virtual FText GetProgressText_Implementation() override;

private:
	// Internal function to handle when a sub-step finishes
	UFUNCTION()
	void OnStepCompleted(UObjectiveBase* CompletedStep);
};