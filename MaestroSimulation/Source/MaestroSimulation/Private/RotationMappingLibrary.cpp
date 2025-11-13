#include "RotationMappingLibrary.h"

FRotator URotationMappingLibrary::MapControllerToHandRotation(
	const FRotator& ControllerRotation,
	const FRotator& ControllerNeutralRotation,
	const FRotator& HandNeutralRotation)
{
	// Convert to Quaternions to avoid gimbal lock
	const FQuat ControllerQuat = ControllerRotation.Quaternion();
	const FQuat ControllerNeutralQuat = ControllerNeutralRotation.Quaternion();
	const FQuat HandNeutralQuat = HandNeutralRotation.Quaternion();

	// Calculate the offset between hand and controller neutral orientations
	// Offset = HandNeutral * Inverse(ControllerNeutral)
	const FQuat OffsetQuat = HandNeutralQuat * ControllerNeutralQuat.Inverse();

	// Apply the offset to the live controller rotation
	// Result = ControllerLive * Offset
	const FQuat FinalQuat = ControllerQuat * OffsetQuat;

	// Return as rotator for use in Blueprints
	return FinalQuat.Rotator();
}
