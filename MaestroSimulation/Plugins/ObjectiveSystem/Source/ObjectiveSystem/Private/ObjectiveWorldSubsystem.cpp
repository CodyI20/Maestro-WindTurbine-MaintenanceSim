#include "ObjectiveWorldSubsystem.h"

void UObjectiveWorldSubsystem::BroadcastObjectiveEvent(FName Tag, int32 Value)
{
	OnObjectiveEventReported.Broadcast(Tag, Value);
}