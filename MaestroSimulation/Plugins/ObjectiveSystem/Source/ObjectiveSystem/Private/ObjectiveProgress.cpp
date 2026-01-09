#include "ObjectiveProgress.h"

void UObjectiveProgress::ActivateObjective(UObject* WorldContextObject)
{
	Super::ActivateObjective(WorldContextObject);
	CurrentAmount = 0;
}

void UObjectiveProgress::OnExternalEvent_Implementation(FName EventTag, float Value)
{
	if (bIsCompleted) return;

	// Only process if the tag matches (e.g., "Pick_up_tool" == "Pick_up_tool")
	if (EventTag == TargetEventTag)
	{
		// Default value is 1)
		CurrentAmount += Value;
		
		if (CurrentAmount >= TargetAmount)
		{
			CurrentAmount = TargetAmount;
			CompleteObjective();
		}
		else
		{
			// Notify UI
			OnObjectiveProgress.Broadcast(this);
		}
	}
}

FText UObjectiveProgress::GetProgressText_Implementation()
{
	if (bIsCompleted) return FText::FromString("Done");
    
	// Returns format: "3 / 10"
	return FText::Format(FText::FromString("{0} / {1}"), CurrentAmount, TargetAmount);
}