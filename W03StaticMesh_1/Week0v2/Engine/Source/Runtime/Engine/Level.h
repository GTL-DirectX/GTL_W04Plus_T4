#pragma once

#include "UObject/ObjectMacros.h"

class AActor;
class UObject;

class ULevel : public UObject
{
    DECLARE_CLASS(ULevel, UObject)

public:
    ULevel();
    virtual ~ULevel();

    virtual void Initialize();
    virtual void Tick(float DeltaTime);
    virtual void Release();

    void AddPendingActor(AActor* Actor);

    void AddActor(AActor* Actor);
    void RemoveActor(AActor* Actor);
    TArray<AActor*> GetActors();

    // EditorManager 같은데로 보내기
    AActor* GetSelectedActor() const { return SelectedActor; }
    void SetPickedActor(AActor* InActor)
    {
        SelectedActor = InActor;
    }

protected:
    TArray<class AActor*> Actors;

private:
    /** Actor가 Spawn되었고, 아직 BeginPlay가 호출되지 않은 Actor들 */
    TArray<AActor*> PendingBeginPlayActors;
    AActor* SelectedActor = nullptr;
};

