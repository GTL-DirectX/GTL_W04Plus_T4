#include "Engine.h"
#include "UObject/Object.h"
#include "UObject/ObjectFactory.h"
#include "World/World.h"


UEngine* GEngine = nullptr;

void UEngine::Init()
{



}

UWorld* UEngine::GetWorldFromContextObject(const UObject* Object) const
{
    if (Object == nullptr)
    {
        UE_LOG(LogLevel::Warning, "Object is nullptr. Can not return World");
        return nullptr;
    }
    return Object->GetWorld();
}

FWorldContext& UEngine::CreateNewWorldContext(EWorldType WorldType)
{
    FWorldContext* NewWorldContext = new FWorldContext();
    NewWorldContext->WorldType = WorldType;
    FString Name = FString("Context_") + std::to_string(NextWorldContextHandle++);
    NewWorldContext->ContextHandle = Name;
    NewWorldContext->SetCurrentWorld(FObjectFactory::ConstructObject<UWorld>(this));

    WorldContexts.Add(*NewWorldContext);
    return *NewWorldContext;
}
