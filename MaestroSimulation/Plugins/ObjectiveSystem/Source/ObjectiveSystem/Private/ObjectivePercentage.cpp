#include "ObjectivePercentage.h"

void UObjectivePercentage::ActivateObjective(UObject* WorldContextObject)
{
	Super::ActivateObjective(WorldContextObject);
	CurrentPercentage = 0.0f;
}

void UObjectivePercentage::OnExternalProgress_Implementation(FName EventTag, float Value)
{
	if (bIsCompleted) return;

	if (EventTag == TargetEventTag)
	{
		if (bAccumulateValues)
		{
			CurrentPercentage += Value;
		}
		else
		{
			// Absolute update (e.g. The canvas says "I am now 0.45 painted")
			CurrentPercentage = Value;
		}

		// Avoid UI oddities
		if(CurrentPercentage > 1.0f) CurrentPercentage = 1.0f;

		// Check if target is hit
		if (CurrentPercentage >= TargetPercentage)
		{
			CurrentPercentage = TargetPercentage;
			CompleteObjective();
		}
		else
		{
			OnObjectiveProgress.Broadcast(this);
		}
	}
}

FText UObjectivePercentage::GetProgressText_Implementation()
{
	if (bIsCompleted) return FText::FromString("Completed");

	// Formats as percentage: "45%"
	return FText::AsPercent(CurrentPercentage);
}