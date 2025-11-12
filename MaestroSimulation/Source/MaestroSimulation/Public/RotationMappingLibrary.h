#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RotationMappingLibrary.generated.h"

/**
 * A simple Blueprint-accessible library that maps a controller rotation 
 * to a hand bone rotation using neutral orientation alignment.
 */
UCLASS()
class MAESTROSIMULATION_API URotationMappingLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    /**
     * Maps the controller rotation to the hand rotation so that the controller’s 
     * neutral orientation matches the hand’s neutral orientation.
     *
     * @param ControllerRotation The current controller rotation (live).
     * @param ControllerNeutralRotation The controller’s neutral rotation (when held naturally).
     * @param HandNeutralRotation The hand’s neutral rotation (the bone’s 0,0,0 pose).
     * @return The corrected rotation that can be directly applied to the hand bone.
     */
    UFUNCTION(BlueprintPure, Category = "VR|Animation")
    static FRotator MapControllerToHandRotation(
        const FRotator& ControllerRotation,
        const FRotator& ControllerNeutralRotation,
        const FRotator& HandNeutralRotation
    );
};
