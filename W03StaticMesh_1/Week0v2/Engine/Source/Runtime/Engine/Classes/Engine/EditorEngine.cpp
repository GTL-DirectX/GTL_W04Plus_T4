#include "EditorEngine.h"
#include "World/World.h"

void UEditorEngine::Init()
{
    Super::Init();
    FWorldContext& InitialWorldContext = CreateNewWorldContext(EWorldType::Editor);
    EditorWorld = InitialWorldContext.World();
    EditorWorld->Initialize();

    /*FWorldContext& PlayWorldContext = CreateNewWorldContext(EWorldType::Game);
    PlayWorld = PlayWorldContext.World();
    PlayWorld->Initialize();*/

    GWorld = EditorWorld;
}

void UEditorEngine::Tick(float DeltaSeconds)
{
    if (GWorld)
    {
        GWorld->Tick(DeltaSeconds);
    }
}

FWorldContext* UEditorEngine::GetWorldContext(EWorldType InType, const FString& InName)
{
    for (FWorldContext& WorldContext : WorldContexts)
    {
        if (WorldContext.WorldType == InType && WorldContext.ContectName == InName)
        {
            return &WorldContext;
        }
    }
    return nullptr;
}
