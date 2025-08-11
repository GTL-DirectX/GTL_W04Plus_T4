#include "Editor.h"
#include "Engine/Engine.h"
#include "World/World.h"

UEditorEngine* GEditor = nullptr;

/*-----------------------------------------------------------------------------
    PIE helpers.
-----------------------------------------------------------------------------*/
/**
 * Sets GWorld to the passed in PlayWorld and sets a global flag indicating that we are playing
 * in the Editor.
 *
 * @param	PlayInEditorWorld		PlayWorld
 * @return	the original GWorld
 */
UWorld* SetPlayInEditorWorld(UWorld* PlayInEditorWorld)
{
    //check(!GIsPlayInEditorWorld);
    UWorld* SavedWorld = GWorld;
    GWorld = PlayInEditorWorld;

    return SavedWorld;
}