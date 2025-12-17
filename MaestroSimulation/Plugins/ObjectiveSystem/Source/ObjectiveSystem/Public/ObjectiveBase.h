#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectiveBase.generated.h"

// Delegate to notify UI or Manager when progress changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveUpdate, UObjectiveBase*, UpdatedObjective);

/**
 * Base class for all objectives.
 * EditInlineNew allows for the creation of instances for this directly inside the Manager's list in the Editor.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class OBJECTIVESYSTEM_API UObjectiveBase : public UObject
{
    GENERATED_BODY()

public:
    // -- Configuration --

    // Unique ID to reference this objective from code/triggers
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    FName ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    FText Title;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (MultiLine = true))
    FText Description;

    // -- State --

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsCompleted;

    // -- Events --

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnObjectiveUpdate OnObjectiveCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnObjectiveUpdate OnObjectiveProgress;

    // -- Functions --
    
    virtual void ActivateObjective(UObject* WorldContextObject);

    // Call this to force the completion of an objective
    UFUNCTION(BlueprintCallable, Category = "Objective")
    virtual void CompleteObjective();

    // The main way the game talks to the objective. 
    // Derived classes will override this to check specific conditions (e.g., "PickedUpTool", 1).
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Objective")
    void OnExternalEvent(FName EventTag, int32 Value);
    
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Objective")
    void OnExternalProgress(FName EventTag, float Value);

    virtual void OnExternalEvent_Implementation(FName EventTag, int32 Value);

    // Helper to get formatted status (e.g. "5/10")
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "UI")
    FText GetProgressText();
};