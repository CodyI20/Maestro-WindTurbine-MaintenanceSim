#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveWorldSubsystem.generated.h"

// The signature for the broadcast
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveEvent, FName, EventTag, int32, Value);

/**
 * A global router for objective events.
 */
UCLASS()
class OBJECTIVESYSTEM_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// The "Radio Frequency" that managers listen to
	UPROPERTY(BlueprintAssignable, Category = "Objective System")
	FOnObjectiveEvent OnObjectiveEventReported;

	// Called by any actor involved in the quest system (e.g. bristle blaster, drone)
	UFUNCTION(BlueprintCallable, Category = "Objective System", meta=(WorldContext="WorldContextObject"))
	void BroadcastObjectiveEvent(FName Tag, int32 Value = 1);
};