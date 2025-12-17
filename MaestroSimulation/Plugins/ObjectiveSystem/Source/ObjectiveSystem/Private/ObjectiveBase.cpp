#include "ObjectiveBase.h"

void UObjectiveBase::ActivateObjective(UObject* WorldContextObject)
{
	bIsCompleted = false;
	// Potential bind event logic
}

void UObjectiveBase::CompleteObjective()
{
	if (bIsCompleted) return;

	bIsCompleted = true;
	OnObjectiveCompleted.Broadcast(this);
}

void UObjectiveBase::OnExternalEvent_Implementation(FName EventTag, int32 Value)
{
	// Default behavior: do nothing
	// Allows specific objectives to ignore events they don't care about.
}

void UObjectiveBase::OnExternalProgress_Implementation(FName EventTag, float Value)
{
	// Default behavior: do nothing.
	// To be overriden in derived classes.
}

FText UObjectiveBase::GetProgressText_Implementation()
{
	if(bIsCompleted) return FText::FromString("Completed");
	return FText::FromString("Active");
}