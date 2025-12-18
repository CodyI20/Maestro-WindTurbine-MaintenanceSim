// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObjectiveSystem.h"

#define LOCTEXT_NAMESPACE "FObjectiveSystemModule"

void FObjectiveSystemModule::StartupModule()
{
	// NOTE: This code will execute after the module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FObjectiveSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// it shall be called before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FObjectiveSystemModule, ObjectiveSystem)