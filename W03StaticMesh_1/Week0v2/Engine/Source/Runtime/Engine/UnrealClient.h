#pragma once
#include "Define.h" 
#include <d3d11.h>

#include "ViewportClient.h"

enum class EViewScreenLocation
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

/**
 * Encapsulates the I/O of a viewport.
 * The viewport display is implemented using the platform independent RHI.
 */
class FViewport
{
public:
    FViewport();
    FViewport(EViewScreenLocation _viewLocation) : viewLocation(_viewLocation) {}
    // Constructor.
    FViewport(FViewportClient* InViewportClient);
    // Destructor
    virtual ~FViewport();

    /**
     * Updates the viewport's displayed pixels with the results of calling ViewportClient->Draw.
     *
     * @param	bShouldPresent	Whether we want this frame to be presented
     */
    //void Draw(bool bShouldPresent = true);

    void Initialize();
    void ResizeViewport(const DXGI_SWAP_CHAIN_DESC& swapchaindesc);
    void ResizeViewport(FRect Top, FRect Bottom, FRect Left, FRect Right);
    void ResizeViewport(FRect newRect);

private:
    D3D11_VIEWPORT viewport;            // 뷰포트 정보
    EViewScreenLocation viewLocation;   // 뷰포트 위치
public:
    D3D11_VIEWPORT& GetViewport() { return viewport; }
    void SetViewport(D3D11_VIEWPORT _viewport) { viewport = _viewport; }
};

