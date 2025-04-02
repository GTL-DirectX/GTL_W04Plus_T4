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

    /** A pointer to a UWorld that is the duplicated/saved-loaded to be played in with "Play From Here" */	
    UWorld* PlayWorld;

    /** When Simulating In Editor, a pointer to the original (non-simulating) editor world */
    UWorld* EditorWorld;

public:

    /** Returns the WorldContext for the editor world. For now, there will always be exactly 1 of these in the editor.
     *
     * @param	bEnsureIsGWorld		Temporarily allow callers to validate that this maps to GWorld to help track down any conversion bugs
     */
    FWorldContext& GetEditorWorldContext(bool bEnsureIsGWorld = false);

    /**
     * Returns the WorldContext for the PIE world, by default will get the first one which will be the server or simulate instance.
     * You need to iterate the context list if you want all the pie world contexts.
     */
    FWorldContext* GetPIEWorldContext(int32 WorldPIEInstance = 0);
};