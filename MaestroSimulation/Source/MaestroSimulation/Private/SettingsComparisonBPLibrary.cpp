// SettingsComparisonBPLibrary.cpp
#include "SettingsComparisonBPLibrary.h"
#include "UObject/UnrealType.h"
#include "GameFramework/SaveGame.h"


FProperty* USettingsComparisonBPLibrary::FindPropertyByName(USaveGame* SaveGameObject, const FName& PropertyName)
{
    if (!SaveGameObject)
        return nullptr;

    for (TFieldIterator<FProperty> PropIt(SaveGameObject->GetClass()); PropIt; ++PropIt)
    {
        FProperty* Property = *PropIt;
        if (Property->GetFName() == PropertyName)
        {
            return Property;
        }
    }
    return nullptr;
}

bool USettingsComparisonBPLibrary::HasFloatChanged(USaveGame* SaveGameObject, FName PropertyName, float CurrentValue, float Tolerance)
{
    FProperty* Property = FindPropertyByName(SaveGameObject, PropertyName);
    if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
    {
        const void* ValuePtr = FloatProp->ContainerPtrToValuePtr<void>(SaveGameObject);
        float SavedValue = FloatProp->GetFloatingPointPropertyValue(ValuePtr);
        return !FMath::IsNearlyEqual(SavedValue, CurrentValue, Tolerance);
    }
    return true; // If the property is not found or there is a type mismatch, assume change
}

bool USettingsComparisonBPLibrary::HasBoolChanged(USaveGame* SaveGameObject, FName PropertyName, bool CurrentValue)
{
    FProperty* Property = FindPropertyByName(SaveGameObject, PropertyName);
    if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Property))
    {
        const void* ValuePtr = BoolProp->ContainerPtrToValuePtr<void>(SaveGameObject);
        bool SavedValue = BoolProp->GetPropertyValue(ValuePtr);
        return SavedValue != CurrentValue;
    }
    return true; // If the property is not found or there is a type mismatch, assume change
}

bool USettingsComparisonBPLibrary::HasStringChanged(USaveGame* SaveGameObject, FName PropertyName, const FString& CurrentValue)
{
    FProperty* Property = FindPropertyByName(SaveGameObject, PropertyName);
    if (FStrProperty* StrProp = CastField<FStrProperty>(Property))
    {
        const void* ValuePtr = StrProp->ContainerPtrToValuePtr<void>(SaveGameObject);
        FString SavedValue = StrProp->GetPropertyValue(ValuePtr);
        return !SavedValue.Equals(CurrentValue, ESearchCase::CaseSensitive);
    }
    return true; // If the property is not found or there is a type mismatch, assume change
}

bool USettingsComparisonBPLibrary::HasIntChanged(USaveGame* SaveGameObject, FName PropertyName, int32 CurrentValue)
{
    FProperty* Property = FindPropertyByName(SaveGameObject, PropertyName);
    if (FIntProperty* IntProp = CastField<FIntProperty>(Property))
    {
        const void* ValuePtr = IntProp->ContainerPtrToValuePtr<void>(SaveGameObject);
        int32 SavedValue = IntProp->GetSignedIntPropertyValue(ValuePtr);
        return SavedValue != CurrentValue;
    }
    return true; // If the property is not found or there is a type mismatch, assume change
}
