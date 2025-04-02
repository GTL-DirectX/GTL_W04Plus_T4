#include "World/World.h"

#include "Editor.h"
#include "Engine/EditorEngine.h"
#include "WorldContext.h"
#include "Actors/Player.h"
#include "BaseGizmos/TransformGizmo.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Level.h"

UWorld* GWorld = nullptr;

UWorld::UWorld()
    : Camera(nullptr)
    , EditorPlayer(nullptr)
    , WorldType(EWorldType::Editor)
{
}

UWorld::~UWorld()
{
}

void UWorld::Initialize(EWorldType InWorldType)
{
    CreateBaseObject();
    ULevel* NewLevel = FObjectFactory::ConstructObject<ULevel>(this);
    SetCurrentLevel(NewLevel);
    CurrentLevel->Initialize();
    WorldType = InWorldType;
}

void UWorld::Tick(float DeltaTime)
{
    if (LocalGizmo)
        LocalGizmo->Tick(DeltaTime);
    if (EditorPlayer)
        EditorPlayer->Tick(DeltaTime);

    if (Camera)
        Camera->TickComponent(DeltaTime);

    if (CurrentLevel)
    {
        CurrentLevel->Tick(DeltaTime);
    }
}

void UWorld::Release()
{
    CurrentLevel->Release();
    delete CurrentLevel;
    ReleaseBaseObject();
}

UWorld* UWorld::GetWorld() const
{
    return const_cast<UWorld* > (this);
}

UWorld* UWorld::DuplicateWorldForPIE(UWorld* OwningWorld)
{
    FWorldContext& InitialWorldContext = GEditor->CreateNewWorldContext(EWorldType::PIE);
    UWorld* PIEWorld = InitialWorldContext.World();
    ULevel* PIELevel = PIEWorld->GetCurrentLevel();

    for (AActor* Actor : OwningWorld->GetCurrentLevel()->GetActors())
    {
        if (Actor)
        {
            if (AActor* DuplicatedActor = Cast<AActor>(Actor->Duplicate()))
            {
                PIELevel->AddActor(DuplicatedActor);
            }
        }
    }

    return PIEWorld;
}

void UWorld::InitializeActorsForPlay() const
{
    for (AActor* Actor : CurrentLevel->GetActors())
    {
        if (Actor)
        {
            Actor->BeginPlay();
        }
    }
}

bool UWorld::IsPIEWorld() const
{
    return WorldType == EWorldType::PIE;
}

void UWorld::CleanupWorld() const
{
    CurrentLevel->Release();
    delete CurrentLevel;
}

void UWorld::CreateBaseObject()
{
    if (EditorPlayer == nullptr)
    {
        EditorPlayer = FObjectFactory::ConstructObject<AEditorPlayer>(this);
    }

    if (Camera == nullptr)
    {
        Camera = FObjectFactory::ConstructObject<UCameraComponent>(this);
        Camera->SetLocation(FVector(8.0f, 8.0f, 8.f));
        Camera->SetRotation(FVector(0.0f, 45.0f, -135.0f));
    }

    if (LocalGizmo == nullptr)
    {
        LocalGizmo = FObjectFactory::ConstructObject<UTransformGizmo>(this);
    }
}

void UWorld::ReleaseBaseObject()
{
    if (LocalGizmo)
    {
        delete LocalGizmo;
        LocalGizmo = nullptr;
    }

    if (WorldGizmo)
    {
        delete WorldGizmo;
        WorldGizmo = nullptr;
    }

    if (Camera)
    {
        delete Camera;
        Camera = nullptr;
    }

    if (EditorPlayer)
    {
        delete EditorPlayer;
        EditorPlayer = nullptr;
    }
}

void UWorld::SetPickingGizmo(UObject* Object)
{
	PickingGizmo = Cast<USceneComponent>(Object);
}

#if WITH_EDITORONLY_DATA
/** Set the CurrentLevel for this world. **/
bool UWorld::SetCurrentLevel(class ULevel* InLevel)
{
    bool bChanged = false;
    if (CurrentLevel != InLevel)
    {
        //ULevel* OldLevel = CurrentLevel;
        CurrentLevel = InLevel;
        bChanged = true;

        //FWorldDelegates::OnCurrentLevelChanged.Broadcast(CurrentLevel, OldLevel, this);
    }
    return bChanged;
}
#endif

/** Get the CurrentLevel for this world. **/
ULevel* UWorld::GetCurrentLevel() const
{
#if WITH_EDITORONLY_DATA
    return CurrentLevel;
#else
    return PersistentLevel;
#endif
}