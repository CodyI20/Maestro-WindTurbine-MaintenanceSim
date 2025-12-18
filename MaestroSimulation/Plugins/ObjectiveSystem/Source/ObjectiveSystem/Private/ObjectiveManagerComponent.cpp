#include "ObjectiveManagerComponent.h"
#include "Engine/World.h"
#include "ObjectiveWorldSubsystem.h"

UObjectiveManagerComponent::UObjectiveManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UObjectiveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Move start objectives to active list and initialize them
	for (UObjectiveBase* Obj : StartObjectives)
	{
		if (Obj)
		{
			// Duplicate the object so the asset template won't be modified
			UObjectiveBase* NewObj = DuplicateObject<UObjectiveBase>(Obj, this);
			AddObjective(NewObj);
		}
	}

	// Find the Subsystem
	if (UWorld* World = GetWorld())
	{
		if (UObjectiveWorldSubsystem* Subsystem = World->GetSubsystem<UObjectiveWorldSubsystem>())
		{
			// Subscribe to the radio station -kzzt-
			Subsystem->OnObjectiveEventReported.AddDynamic(this, &UObjectiveManagerComponent::HandleSubsystemEvent);
		}
	}
}

void UObjectiveManagerComponent::AddObjective(UObjectiveBase* NewObjective)
{
	if (!NewObjective) return;

	ActiveObjectives.Add(NewObjective);
	NewObjective->ActivateObjective(GetWorld());

	NewObjective->OnObjectiveCompleted.AddDynamic(this, &UObjectiveManagerComponent::HandleObjectiveCompleted);

	// No focus yet -> auto-focus this new one.
	if (TrackedObjective == nullptr)
	{
		SetTrackedObjective(NewObjective);
	}
    
	// Sanity-check
	UE_LOG(LogTemp, Warning, TEXT("Objective Added: %s"), *NewObjective->Title.ToString());
}

void UObjectiveManagerComponent::SetTrackedObjective(UObjectiveBase* NewTracked)
{
	TrackedObjective = NewTracked;
	OnTrackedObjectiveChanged.Broadcast(NewTracked);
}

void UObjectiveManagerComponent::ReportEvent(FName EventTag, int32 Value)
{
	// Loop through all the active objectives and pass the event down
	for (UObjectiveBase* Obj : ActiveObjectives)
	{
		if (Obj && !Obj->bIsCompleted)
		{
			Obj->OnExternalEvent(EventTag, Value);
		}
	}
}

void UObjectiveManagerComponent::ReportProgress(FName EventTag, float Value)
{
	for (UObjectiveBase* Obj : ActiveObjectives)
	{
		if (Obj && !Obj->bIsCompleted)
		{
			Obj->OnExternalProgress(EventTag, Value);
		}
	}
}

// Forward the call from the subsystem
void UObjectiveManagerComponent::HandleSubsystemEvent(FName Tag, int32 Value)
{
	ReportEvent(Tag, Value);
}

void UObjectiveManagerComponent::HandleObjectiveCompleted(UObjectiveBase* CompletedObjective)
{
	// If the one that just finished was our "Main Focus"...
	if (TrackedObjective == CompletedObjective)
	{
		// ...we need to find a new one!
		FindNextTrackedObjective();
	}
}

void UObjectiveManagerComponent::FindNextTrackedObjective()
{
	// Loop through all objectives to find the first one that is NOT done
	for (UObjectiveBase* Obj : ActiveObjectives)
	{
		if (Obj && !Obj->bIsCompleted)
		{
			SetTrackedObjective(Obj);
			return; // Found one! Stop looking.
		}
	}

	// If we get here, the player has finished EVERYTHING.
	SetTrackedObjective(nullptr);
}

UObjectiveBase* UObjectiveManagerComponent::GetObjectiveByID(FName ID)
{
	for (UObjectiveBase* Obj : ActiveObjectives)
	{
		if (Obj && Obj->ObjectiveID == ID)
		{
			return Obj;
		}
	}
	return nullptr;
}