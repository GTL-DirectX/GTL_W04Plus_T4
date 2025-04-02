#pragma once

#include "WorldType.h"
#include "Container/String.h"
#include "UObject/NameTypes.h"

class UWorld;

struct FWorldContext
{
    // 현재 월드의 타입.
    EWorldType WorldType;

    FName ContextHandle;

    UWorld* World() const
    {
        return ThisCurrentWorld;
    }

    void SetCurrentWorld(UWorld* InWorld);

    //UGameInstance* OwningGameInstance;

    FWorldContext()
        : WorldType(EWorldType::None)
        , ContextHandle(TEXT("None"))
        //, GameViewport(nullptr)
        //, OwningGameInstance(nullptr)
        //, PIEInstance(INDEX_NONE)
        //, PIEWorldFeatureLevel(ERHIFeatureLevel::Num)
        //, RunAsDedicated(false)
        //, bWaitingOnOnlineSubsystem(false)
        //, bIsPrimaryPIEInstance(false)
        //, AudioDeviceID(INDEX_NONE)
        , ThisCurrentWorld(nullptr)
    {}

private:
    // 현재 월드 포인터.
    UWorld* ThisCurrentWorld;
};

