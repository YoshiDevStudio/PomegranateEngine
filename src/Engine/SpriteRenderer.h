#pragma once

#include "DLL_Build.h"

#include "SDL3/SDL.h"
#include "Transform2D.h"
#include "Texture2D.h"
#include "File.h"
#include "Window.h"

class Window;

class DLL_API SpriteRenderer : public Component
{
public:
    SpriteRenderer(Window* window);
    SpriteRenderer(Window* window, Texture2D* tex2D);
    SpriteRenderer(Window* window, std::string texName);

    ~SpriteRenderer() = default;

    virtual void Update() override;

    void SetTexture(Texture2D* tex2D);
    void SetTexture(std::string texName);
    Texture2D* GetTexture();

    //will clip texture outside of clipRect bounds
    //clipRect is set to full texture size by default
    glm::vec2 clipRect;
private:
    void Draw();

    Texture2D* tex2D = nullptr;
    Window* window;
};