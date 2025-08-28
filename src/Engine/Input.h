#pragma once

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>

#include "Core.h"
#include "Event.h"

class DLL_API Input
{
public:
    static void Initialize();
    static void Uninitialize();
    static void OnEvent(SDL_Event* e);
    
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static glm::vec2 GetScreenMousePosition();
    static glm::vec2 GetWorldMousePosition();
    static bool IsMouseButtonPressed(SDL_MouseButtonFlags button);
    static bool IsMouseButtonReleased(SDL_MouseButtonFlags button);

    static glm::vec2 MakeVector(int upKey, int downKey, int rightKey, int leftKey);

    static Event<void, SDL_Event*>* OnMouseWheelEvent;
};