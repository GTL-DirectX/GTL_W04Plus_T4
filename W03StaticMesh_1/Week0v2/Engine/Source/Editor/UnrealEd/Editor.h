#pragma once
#include "World/World.h"

/** The editor object. */
extern class UEditorEngine* GEditor;

/**
 * Sets GWorld to the passed in PlayWorld and sets a global flag indicating that we are playing
 * in the Editor.
 *
 * @param	PlayInEditorWorld		PlayWorld
 * @return	the original GWorld
 */
UWorld* SetPlayInEditorWorld(UWorld* PlayInEditorWorld);

/**
 * Restores GWorld to the passed in one and reset the global flag indicating whether we are a PIE
 * world or not.
 *
 * @param EditorWorld	original world being edited
 */
void RestoreEditorWorld(UWorld* EditorWorld);