#include "EditorEngine.h"
#include "Editor.h"
#include "World/World.h"
#include "level.h"
#include "GameFramework/Actor.h"

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
    GEditor = this;
}

void UEditorEngine::Tick(float DeltaSeconds)
{
    // Editor 전용 액터 Tick 처리
    for (FWorldContext& WorldContext : WorldContexts)
    {
        GWorld->Tick(DeltaSeconds);
        //UWorld* EditorWorld = WorldContext.World();
        //EditorWorld->Tick(DeltaSeconds);
        //if (EditorWorld && EditorWorld->WorldType == EWorldType::Editor)
        //{
        //    ULevel* Level = EditorWorld->GetCurrentLevel();
        //    {
        //        for (AActor* Actor : Level->GetActors())
        //        {
        //            if (Actor && Actor->IsTickInEditor())
        //            {
        //                Actor->Tick(DeltaSeconds);
        //            }
        //        }
        //    }
        //}
        //else if (EditorWorld && EditorWorld->WorldType == EWorldType::PIE)
        //{
        //    ULevel* Level = EditorWorld->GetCurrentLevel();
        //    {
        //        for (AActor* Actor : Level->GetActors())
        //        {
        //            if (Actor)
        //            {
        //                Actor->Tick(DeltaSeconds);
        //            }
        //        }
        //    }
        //}
    }
}

FWorldContext* UEditorEngine::GetWorldContext(EWorldType InType, const FString& InName)
{
    for (FWorldContext& WorldContext : WorldContexts)
    {
        if (WorldContext.WorldType == InType && WorldContext.ContextHandle == InName)
        {
            return &WorldContext;
        }
    }
    return nullptr;
}

FWorldContext& UEditorEngine::GetEditorWorldContext(bool bEnsureIsGWorld)
{
    for (int32 i = 0; i < WorldContexts.Num(); ++i)
    {
        if (WorldContexts[i].WorldType == EWorldType::Editor)
        {
            if (!bEnsureIsGWorld || WorldContexts[i].World() == GetWorld())
            {
                return WorldContexts[i];
            }
        }
    }

    //check(false); // There should have already been one created in UEngine::Init
    return CreateNewWorldContext(EWorldType::Editor);
}

FWorldContext* UEditorEngine::GetPIEWorldContext(int32 WorldPIEInstance)
{
    for (FWorldContext& WorldContext : WorldContexts)
    {
        // @todo Check PIEInstance
        if (WorldContext.WorldType == EWorldType::PIE)
        {
            return &WorldContext;
        }
    }

    return nullptr;
}