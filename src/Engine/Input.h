#pragma once

#include <SDL3/SDL.h>

#include "Core.h"

//!!TODO: Implement Mouse Events, Keymods, Gamepads
class Input
{
public:
    enum KeyEventType
    {
        KeyUp,
        KeyDown
    };
    struct KeyEvent
    {
        int key;
        KeyEventType type;
        SDL_Keymod mod;

        //if key is -1, key is invalid
        KeyEvent(int key = -1, KeyEventType type = KeyEventType::KeyDown, SDL_Keymod mod = SDL_KMOD_NONE)
        {
            this->key = key;
            this->type = type;
            this->mod = mod;
        }
    };
public:
    static void Initialize();
    static void Uninitialize();
    static void OnKeyEvent(KeyEvent e);
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

    static Event<void, KeyEvent>* keyEvent;

private:
    static bool keys[322];
};