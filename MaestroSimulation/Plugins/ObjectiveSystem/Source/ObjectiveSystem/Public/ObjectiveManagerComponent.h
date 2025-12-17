#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveBase.h"
#include "ObjectiveManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTIVESYSTEM_API UObjectiveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObjectiveManagerComponent();

private:
	UFUNCTION()
	void HandleSubsystemEvent(FName Tag, int32 Value);

protected:
	virtual void BeginPlay() override;

public:	
	// To be filled in the Editor.
	// Instanced means the object data is saved right here in the component.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Objectives")
	TArray<UObjectiveBase*> StartObjectives;

	// The runtime list of active objectives
	UPROPERTY(BlueprintReadOnly, Category = "Objectives")
	TArray<UObjectiveBase*> ActiveObjectives;

	// Add a new objective dynamically
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void AddObjective(UObjectiveBase* NewObjective);

	// To be called when something happens in game (e.g. "PickUpTool", 1)
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void ReportEvent(FName EventTag, int32 Value = 1);

	// Continuous progress (e.g. 0.5 for 50%)
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void ReportProgress(FName EventTag, float Value);

	// The objective currently being highlighted in the UI
	UPROPERTY(BlueprintReadOnly, Category = "Objectives")
	UObjectiveBase* TrackedObjective;

	// Change the active quest
	UFUNCTION(BlueprintCallable, Category = "Objectives")
	void SetTrackedObjective(UObjectiveBase* NewTracked);

	// Helper to find an objective by ID
	UFUNCTION(BlueprintPure, Category = "Objectives")
	UObjectiveBase* GetObjectiveByID(FName ID);
};