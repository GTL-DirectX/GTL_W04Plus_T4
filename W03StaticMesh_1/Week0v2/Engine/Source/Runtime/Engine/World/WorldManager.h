#pragma once

#include "Container/Array.h"
#include "Container/String.h"
#include "WorldContext.h"

class UWorld;

class FWorldManager
{

private:
    TArray<FWorldContext> WorldContexts;

public:
    FWorldContext& AddWorld(EWorldType InType, const FString& InName);

};

