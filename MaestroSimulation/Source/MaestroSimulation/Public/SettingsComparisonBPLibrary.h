// SettingsComparisonBPLibrary.h
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SettingsComparisonBPLibrary.generated.h"

UCLASS()
class MAESTROSIMULATION_API USettingsComparisonBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    /** Compare a float property by name */
    UFUNCTION(BlueprintPure, Category="Settings|Comparison")
    static bool HasFloatChanged(USaveGame* SaveGameObject, FName PropertyName, float CurrentValue, float Tolerance = 0.01);

    /** Compare a bool property by name */
    UFUNCTION(BlueprintPure, Category="Settings|Comparison")
    static bool HasBoolChanged(USaveGame* SaveGameObject, FName PropertyName, bool CurrentValue);

    /** Compare a string property by name */
    UFUNCTION(BlueprintPure, Category="Settings|Comparison")
    static bool HasStringChanged(USaveGame* SaveGameObject, FName PropertyName, const FString& CurrentValue);

    /** Compare an int property by name */
    UFUNCTION(BlueprintPure, Category="Settings|Comparison")
    static bool HasIntChanged(USaveGame* SaveGameObject, FName PropertyName, int32 CurrentValue);

    /** Generic helper to get a property by name */
    static FProperty* FindPropertyByName(USaveGame* SaveGameObject, const FName& PropertyName);
};
