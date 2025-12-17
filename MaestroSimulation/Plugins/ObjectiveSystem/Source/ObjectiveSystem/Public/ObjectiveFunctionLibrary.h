#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectiveManagerComponent.h"
#include "ObjectiveFunctionLibrary.generated.h"

/**
 * Static helper functions for the Objective System.
 * Accessible from anywhere in Blueprints.
 */
UCLASS()
class OBJECTIVESYSTEM_API UObjectiveFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** * Tries to find the Objective Manager on the local Player Controller.
	 * Returns nullptr if not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Objective System", meta = (WorldContext = "WorldContextObject"))
	static UObjectiveManagerComponent* GetLocalObjectiveManager(const UObject* WorldContextObject);

	/**
	 * Checks if a specific objective ID is complete.
	 */
	UFUNCTION(BlueprintPure, Category = "Objective System", meta = (WorldContext = "WorldContextObject"))
	static bool IsObjectiveComplete(const UObject* WorldContextObject, FName ObjectiveID);

	/**
	 * Gets the display data for an objective by ID. 
	 * Useful for UI to just ask "What text should I show for Quest_01?"
	 * Returns false if objective is not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Objective System", meta = (WorldContext = "WorldContextObject"))
	static bool GetObjectiveDisplayData(const UObject* WorldContextObject, FName ObjectiveID, FText& OutTitle, FText& OutDescription, FText& OutProgress);

	/**
	 * Returns an array of ALL active (incomplete) objectives.
	 * Useful for populating a quest journal.
	 */
	UFUNCTION(BlueprintCallable, Category = "Objective System", meta = (WorldContext = "WorldContextObject"))
	static TArray<UObjectiveBase*> GetAllActiveObjectives(const UObject* WorldContextObject);
};