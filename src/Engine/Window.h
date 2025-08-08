#pragma once

#include "Engine.h"

class Window
{
public:
    Window(SDL_Window* window, SDL_Renderer* renderer);
    ~Window();

    //!!TODO: Implement Mouse Events
    SDL_AppResult OnEvent(SDL_Event* event);
    void FrameUpdate();

private:
    void Initialize(SDL_Window* window, SDL_Renderer* renderer);
    void Uninitialize();

    SDL_Window* sdlWindow = NULL;
    SDL_Renderer* renderer = NULL;

    //Used for calculating deltaTime
    float prevTime;
};