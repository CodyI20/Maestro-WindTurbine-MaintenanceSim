#include "ObjectiveFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UObjectiveManagerComponent* UObjectiveFunctionLibrary::GetLocalObjectiveManager(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;
    
    APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
    if (!PC) return nullptr;
    
    return PC->FindComponentByClass<UObjectiveManagerComponent>();
}

bool UObjectiveFunctionLibrary::IsObjectiveComplete(const UObject* WorldContextObject, FName ObjectiveID)
{
    UObjectiveManagerComponent* Manager = GetLocalObjectiveManager(WorldContextObject);
    if (!Manager) return false;

    UObjectiveBase* Obj = Manager->GetObjectiveByID(ObjectiveID);
    if (Obj)
    {
        return Obj->bIsCompleted;
    }
    return false;
}

bool UObjectiveFunctionLibrary::GetObjectiveDisplayData(const UObject* WorldContextObject, FName ObjectiveID, FText& OutTitle, FText& OutDescription, FText& OutProgress)
{
    UObjectiveManagerComponent* Manager = GetLocalObjectiveManager(WorldContextObject);
    if (!Manager) return false;

    UObjectiveBase* Obj = Manager->GetObjectiveByID(ObjectiveID);
    
    if (Obj)
    {
        OutTitle = Obj->Title;
        OutDescription = Obj->Description;
        OutProgress = Obj->GetProgressText();
        return true;
    }

    return false;
}

TArray<UObjectiveBase*> UObjectiveFunctionLibrary::GetAllActiveObjectives(const UObject* WorldContextObject)
{
    UObjectiveManagerComponent* Manager = GetLocalObjectiveManager(WorldContextObject);
    if (Manager)
    {
        // Filter out completed ones just in case the manager keeps them
        TArray<UObjectiveBase*> Result;
        for (UObjectiveBase* Obj : Manager->ActiveObjectives)
        {
            if (Obj && !Obj->bIsCompleted)
            {
                Result.Add(Obj);
            }
        }
        return Result;
    }

    return TArray<UObjectiveBase*>(); // Return empty if FAILED
}