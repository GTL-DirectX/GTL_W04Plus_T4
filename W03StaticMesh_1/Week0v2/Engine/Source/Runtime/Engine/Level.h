#pragma once

#include "CoreUObject/UObject/Object.h"
#include "UObject/ObjectMacros.h"

class AActor;

class ULevel : public UObject
{
    DECLARE_CLASS(ULevel, UObject)

public:
    TArray<class AActor*> Actors;


};

