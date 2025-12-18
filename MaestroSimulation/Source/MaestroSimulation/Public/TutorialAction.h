#pragma once

#include "CoreMinimal.h"
#include "TutorialAction.generated.h"

class AActor;
class USoundBase;
class UObject;

UENUM(BlueprintType)
enum class ETutorialActionType : uint8
{
	DestroyActor    UMETA(DisplayName = "Destroy Actor"),
	PlaySound       UMETA(DisplayName = "Play Sound"),
	ShowActor       UMETA(DisplayName = "Show Actor"),
	CallActorEvent  UMETA(DisplayName = "Call Actor Event")
};

USTRUCT(BlueprintType)
struct FTutorialAction
{
	GENERATED_BODY()
	
	// The "Switch" variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETutorialActionType ActionType = ETutorialActionType::DestroyActor;

	// --- Conditional Fields ---

	// Visible for Destroy, Show, OR Call Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ActionType == ETutorialActionType::DestroyActor || ActionType == ETutorialActionType::ShowActor || ActionType == ETutorialActionType::CallActorEvent", EditConditionHides))
	TSoftObjectPtr<AActor> Actor;

	// Visible ONLY when ActionType is PlaySound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ActionType == ETutorialActionType::PlaySound", EditConditionHides))
	USoundBase* Sound = nullptr;

	// Visible ONLY when ActionType is TriggerEvent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ActionType == ETutorialActionType::CallActorEvent", EditConditionHides))
	FName EventName;

	// Invisible for now
	UPROPERTY(BlueprintReadWrite)
	UObject* ParameterObject = nullptr;

	// Visible ONLY when ActionType is CheckPlayer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "ActionType == ETutorialActionType::CallActorEvent", EditConditionHides))
	bool IsReferencingPlayer = false;
};