#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveBase.h"
#include "ObjectiveManagerComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrackedObjectiveChanged, UObjectiveBase*, NewTrackedObjective);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTIVESYSTEM_API UObjectiveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectiveManagerComponent();

private:
	UFUNCTION()
	void HandleSubsystemEvent(FName Tag, float Value);

protected:
	virtual void BeginPlay() override;
	// Internal function triggered when ANY objective completes
	UFUNCTION()
	void HandleObjectiveCompleted(UObjectiveBase* CompletedObjective);

public:	
	// To be filled in the Editor.
	// Instanced means the object data is saved right here in the component.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Objectives")
	TArray<UObjectiveBase*> StartObjectives;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTrackedObjectiveChanged OnTrackedObjectiveChanged;

	// The runtime list of active objectives
	UPROPERTY(BlueprintReadOnly, Category = "Objectives")
	TArray<UObjectiveBase*> ActiveObjectives;

	// Add a new objective dynamically
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void AddObjective(UObjectiveBase* NewObjective);

	// To be called when something happens in game (e.g. "PickUpTool", 1)
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void ReportEvent(FName EventTag, float Value = 1);

	// Continuous progress (e.g. 0.5 for 50%)
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void ReportProgress(FName EventTag, float Value);

	// The objective currently being highlighted in the UI
	UPROPERTY(BlueprintReadOnly, Category = "Objectives")
	UObjectiveBase* TrackedObjective;

	// Change the active quest
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void SetTrackedObjective(UObjectiveBase* NewTracked);

	// Helper to find the next incomplete objective
	void FindNextTrackedObjective();

	// Helper to find an objective by ID
	UFUNCTION(BlueprintPure, Category = "Objectives")
	UObjectiveBase* GetObjectiveByID(FName ID);
};