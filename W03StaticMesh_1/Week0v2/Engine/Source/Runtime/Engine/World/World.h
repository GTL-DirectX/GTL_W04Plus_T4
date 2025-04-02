#pragma once
#include "WorldType.h"
#include "Level.h"
#include "UObject/ObjectMacros.h"
#include "CoreUObject/UObject/ObjectFactory.h"

class AActor;
class UObject;
class UGizmoArrowComponent;
class UCameraComponent;
class AEditorPlayer;
class USceneComponent;
class UTransformGizmo;

class UWorld : public UObject
{
    DECLARE_CLASS(UWorld, UObject)

public:
    UWorld();
    virtual ~UWorld();

    virtual void Initialize();
    virtual void Tick(float DeltaTime);
    virtual void Release();

    virtual UWorld* GetWorld() const override;

public:
    UObject* WorldGizmo = nullptr;
    void InitializeActorsForPlay();
    bool IsPIEWorld() const;
    void CleanupWorld();

    /**
     * Level에 Actor를 Spawn합니다.
     * @tparam T AActor를 상속받은 클래스
     * @return Spawn된 Actor의 포인터
     */
    template <typename T>
        requires std::derived_from<T, AActor>
    T* SpawnActor()
    {
        T* NewActor = FObjectFactory::ConstructObject<T>(this);
        CurrentLevel->AddActor(NewActor);
        // TODO: 일단 AddComponent에서 Component마다 초기화
        // 추후에 RegisterComponent() 만들어지면 주석 해제
        // Actor->InitializeComponents();
        //ActorsArray.Add(NewActor);
        CurrentLevel->AddPendingActor(NewActor);
        return NewActor;
    }

protected:
    UCameraComponent* Camera;
    AEditorPlayer* EditorPlayer;
    UTransformGizmo* LocalGizmo = nullptr;

private:
    USceneComponent* PickingGizmo = nullptr;

    void CreateBaseObject();
    void ReleaseBaseObject();

public:
    UCameraComponent* GetCamera() const { return Camera; }
    AEditorPlayer* GetEditorPlayer() const { return EditorPlayer; }
    UTransformGizmo* GetLocalGizmo() const { return LocalGizmo; }

    USceneComponent* GetPickingGizmo() const { return PickingGizmo; }
    void SetPickingGizmo(UObject* Object);

public:
    /** The type of world this is. Describes the context in which it is being used (Editor, Game, Preview etc.) */
    EWorldType WorldType;

private:
    // @todo Hold Multiple Levels in this world
    ///** Array of levels currently in this world. Not serialized to disk to avoid hard references. */
    //TArray<class ULevel*>						Levels;

#if WITH_EDITORONLY_DATA
    /** Pointer to the current level being edited. Level has to be in the Levels array and == PersistentLevel in the game. */
    class ULevel*								CurrentLevel;
#endif

public:
#if WITH_EDITORONLY_DATA
/**
 * Set the CurrentLevel for this world.
 * @return true if the current level changed.
 */
    bool SetCurrentLevel(class ULevel* InLevel);
#endif

    /** Get the CurrentLevel for this world. **/
    class ULevel* GetCurrentLevel() const;

public:
    /** Given a loaded editor UWorld, duplicate it for play in editor purposes with OwningWorld as the world with the persistent level. */
    static UWorld* DuplicateWorldForPIE(UWorld* OwningWorld);//const FString& PackageName, UWorld* OwningWorld);
};

// @todo UWorld*를 UWorldProxy로 래핑
/** Global UWorld pointer. Use of this pointer should be avoided whenever possible. */
extern UWorld* GWorld;