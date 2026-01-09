#include "ObjectiveWorldSubsystem.h"

void UObjectiveWorldSubsystem::BroadcastObjectiveEvent(FName Tag, float Value)
{
	OnObjectiveEventReported.Broadcast(Tag, Value);
}