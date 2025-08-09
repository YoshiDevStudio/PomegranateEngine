#pragma once

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

#include "Engine.h"

class Window
{
public:
    Window(int width, int height, SDL_Window* window, SDL_Renderer* renderer);
    ~Window();

    //!!TODO: Implement Mouse Events
    SDL_AppResult OnEvent(SDL_Event* event);
    void FrameUpdate();

    void SetWindowFlags(SDL_WindowFlags windowFlags);
    SDL_WindowFlags GetWindowFlags();

    void SetWindowRect(glm::ivec2 rect);
    void SetWindowRect(int width, int height);
    glm::ivec2 GetWindowRect();

private:
    SDL_Window* sdlWindow = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_WindowFlags windowFlags = 0;
    glm::ivec2 windowRect = glm::ivec2(0, 0);
    //Used for calculating deltaTime
    float prevTime = 0;
};