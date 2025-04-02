#pragma once

#include "WorldType.h"
#include "Container/String.h"

class UWorld;

struct FWorldContext
{
    // 현재 월드의 타입.
    EWorldType WorldType;
    FString ContectName;

    UWorld* World() const
    {
        return ThisCurrentWorld;
    }

    void SetCurrentWorld(UWorld* InWorld);

    //UGameInstance* OwningGameInstance;

private:
    // 현재 월드 포인터.
    UWorld* ThisCurrentWorld;
};

