#include "ObjectiveSequential.h"
#include "Engine/World.h"

void UObjectiveSequential::ActivateObjective(UObject* WorldContextObject)
{
    Super::ActivateObjective(WorldContextObject);
    CurrentStepIndex = 0;

    // Start the first objective if it exists
    if (Objectives.IsValidIndex(CurrentStepIndex))
    {
        UObjectiveBase* CurrentObj = Objectives[CurrentStepIndex];
        
        // Sub-objectives must be duplicated if they are templates, 
        // HOWEVER, since this container is likely already duplicated by the Manager, the sub-objects are usually safe to use directly.
        
        // Bind to the sub-objective's completion event
        CurrentObj->OnObjectiveCompleted.AddDynamic(this, &UObjectiveSequential::OnStepCompleted);
        
        // Activate the sub-objective
        CurrentObj->ActivateObjective(WorldContextObject);
    }
    else
    {
        // Complete immediately if there is no step (Autocomplete quest?)
        CompleteObjective();
    }
}

void UObjectiveSequential::OnExternalEvent_Implementation(FName EventTag, int32 Value)
{
    if (bIsCompleted) return;

    // Forward the event ONLY to the current active step
    if (Objectives.IsValidIndex(CurrentStepIndex))
    {
        Objectives[CurrentStepIndex]->OnExternalEvent(EventTag, Value);
    }
}

void UObjectiveSequential::OnExternalProgress_Implementation(FName EventTag, float Value)
{
    if (bIsCompleted) return;

    // Forward progress to the current active step
    if (Objectives.IsValidIndex(CurrentStepIndex))
    {
        Objectives[CurrentStepIndex]->OnExternalProgress(EventTag, Value);
    }
}

void UObjectiveSequential::OnStepCompleted(UObjectiveBase* CompletedStep)
{
    // Unbind to prevent double calls - IMPORTANT
    CompletedStep->OnObjectiveCompleted.RemoveDynamic(this, &UObjectiveSequential::OnStepCompleted);

    // Move to the next step
    CurrentStepIndex++;

    if (Objectives.IsValidIndex(CurrentStepIndex))
    {
        // Activate next
        UObjectiveBase* NextObj = Objectives[CurrentStepIndex];
        NextObj->OnObjectiveCompleted.AddDynamic(this, &UObjectiveSequential::OnStepCompleted);
        NextObj->ActivateObjective(GetWorld());
        
        // Notify UI of the progress
        OnObjectiveProgress.Broadcast(this);
    }
    else
    {
        // Done because there are no more steps! Yaaay!
        CompleteObjective();
    }
}

FText UObjectiveSequential::GetProgressText_Implementation()
{
    if (bIsCompleted) return FText::FromString("All Steps Complete");

    // Return the text of the CURRENT sub-objective
    if (Objectives.IsValidIndex(CurrentStepIndex))
    {
        return Objectives[CurrentStepIndex]->GetProgressText();
    }

    return FText::GetEmpty();
}