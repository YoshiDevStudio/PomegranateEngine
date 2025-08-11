#pragma once

#include <SDL3/SDL.h>

#include "Core.h"

//!!TODO: Implement Mouse Events, Keymods, Gamepads
class DLL_API Input
{
public:
    static void Initialize();
    static void Uninitialize();
    static void OnEvent(SDL_Event* e);
    
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static glm::vec2 GetMousePosition();
    static bool IsMouseButtonPressed(SDL_MouseButtonFlags button);
    static bool IsMouseButtonReleased(SDL_MouseButtonFlags button);

    static Event<void, SDL_Event*>* OnMouseWheelEvent;
};