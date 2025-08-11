#pragma once


class FViewport;
class UWorld;

/**
 * An abstract interface to a viewport's client.
 * The viewport's client processes input received by the viewport, and draws the viewport.
 */
class FViewportClient
{
public:
    virtual ~FViewportClient(){}
    //virtual void RedrawRequested(FViewport* Viewport);
    virtual void Draw(FViewport* Viewport) = 0;
    virtual UWorld* GetWorld() const { return NULL; }

    /**
     * Returns true if this viewport is orthogonal.
     * If hit proxies are ever used in-game, this will need to be
     * overridden correctly in GameViewportClient.
     */
    virtual bool IsOrtho() const { return false; }

    // FViewport에서 발생하는 이벤트를 처리하는 가상 함수들
    //virtual void OnInput(const FInputEvent& Event) = 0;
    // FViewport에 대한 참조 (혹은 소유)
};
    