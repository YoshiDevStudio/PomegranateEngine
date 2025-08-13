#pragma once

#include "DLL_Build.h"

#include "SDL3/SDL.h"
#include "Transform2D.h"
#include "Texture2D.h"
#include "File.h"
#include "RenderManager.h"

class DLL_API SpriteRenderer : public Component
{
public:
    SpriteRenderer();
    SpriteRenderer(Texture2D* tex2D);
    SpriteRenderer(std::string texName);

    ~SpriteRenderer() = default;

    virtual void Update() override;

    void SetTexture(Texture2D* tex2D);
    void SetTexture(std::string texName);
    Texture2D* GetTexture();

    void ResetClipRect();

    //will clip texture outside of clipRect bounds
    //clipRect is set to full texture size by default
    SDL_FRect clipRect;
    int zIndex = 0;
    SDL_FlipMode flipMode = SDL_FLIP_NONE;
private:
    void Draw();

    Texture2D* tex2D = nullptr;
};