#pragma once

#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"

#include "Container/Array.h"
#include "World/WorldContext.h"

class UEngine : public UObject
{
    DECLARE_CLASS(UEngine, UObject)


public:
    UEngine() = default;


protected:
    TArray<FWorldContext> WorldContexts;


public:
    virtual void Init();
    virtual void Tick(float DeltaSeconds) = 0;

    UWorld* GetWorldFromContextObject(const UObject* Object) const;

    FWorldContext& CreateNewWorldContext(EWorldType WorldType);

private:
    int32 NextWorldContextHandle = 0;

};

extern class UEngine* GEngine;