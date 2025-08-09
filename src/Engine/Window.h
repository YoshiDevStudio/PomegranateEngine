#pragma once

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

#include "Core.h"
#include "Input.h"

class DLL_API Window
{
public:
    Window(int width, int height, SDL_WindowFlags windowFlags = 0);
    ~Window();

    //!!TODO: Implement Mouse Events
    bool OnEvent(SDL_Event* event);
    void FrameUpdate();

    void SetWindowFlags(SDL_WindowFlags windowFlags);
    SDL_WindowFlags GetWindowFlags();

    void SetWindowRect(glm::ivec2 rect);
    void SetWindowRect(int width, int height);
    glm::ivec2 GetWindowRect();

    static SDL_Window* sdlWindow;
    static SDL_Renderer* renderer;
private:
    

    SDL_WindowFlags windowFlags = 0;
    glm::ivec2 windowRect = glm::ivec2(0, 0);
    //Used for calculating deltaTime
    float prevTime = 0;
};