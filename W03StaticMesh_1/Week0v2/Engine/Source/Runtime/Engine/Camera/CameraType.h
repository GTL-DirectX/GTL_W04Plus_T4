#pragma once
#include "Math/Vector.h"

namespace ECameraProjectionMode
{
    enum Type : int
    {
        Perspective,
        Orthographic
    };
}

struct FMinimalViewInfo
{
    /** Location */
    FVector Location;

    // @todo Use FRotator
    /** Rotation */
    FVector Rotation;

    /** The horizontal field of view (in degrees) in perspective mode (ignored in orthographic mode). */
    float FOV;

    /** The originally desired horizontal field of view before any adjustments to account for different aspect ratios */
    float DesiredFOV;

    /** The desired width (in world units) of the orthographic view (ignored in Perspective mode) */
    float OrthoWidth;

    /** The near plane distance of the orthographic view (in world units) */
    float OrthoNearClipPlane;

    /** The far plane distance of the orthographic view (in world units) */
    float OrthoFarClipPlane;

    /** The near plane distance of the perspective view (in world units). Set to a negative value to use the default global value of GNearClippingPlane */
    float PerspectiveNearClipPlane;

    // Aspect Ratio (Width/Height)
    float AspectRatio;

    // The type of camera
    ECameraProjectionMode::Type ProjectionMode;

    FMinimalViewInfo()
        : Location()
        , Rotation()
        , FOV(90.0f)
        , DesiredFOV(90.0f)
        , OrthoWidth(512.0f)
        , OrthoNearClipPlane(0.0f)
        , OrthoFarClipPlane(2097152.0f) // 2^21, UE4's default far plane distance
        , PerspectiveNearClipPlane(-1.0f)
        , AspectRatio(1.33333333f)
        //, bConstrainAspectRatio(false)
        //, bUseFieldOfViewForLOD(true)
        , ProjectionMode(ECameraProjectionMode::Perspective)
        //, PostProcessBlendWeight(0.0f)
        //, OffCenterProjectionOffset(ForceInitToZero)
    {
    }
};