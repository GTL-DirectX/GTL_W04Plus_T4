#pragma once

#include "Engine.h"

class UEditorEngine : public UEngine
{
    DECLARE_CLASS(UEditorEngine, UEngine)

public:
    UEditorEngine() = default;

public:
    virtual void Init() override;
    virtual void Tick(float DeltaSeconds) override;

    FWorldContext* GetWorldContext(EWorldType InType, const FString& InName);

    UWorld* PlayWorld;
    UWorld* EditorWorld;

};

