#include "Input.h"

Event<void, SDL_Event*>* Input::OnMouseWheelEvent;
//Constructor
void Input::Initialize()
{
    OnMouseWheelEvent = new Event<void, SDL_Event*>();
}

//Deconstructor
void Input::Uninitialize()
{
    delete OnMouseWheelEvent;
}

void Input::OnEvent(SDL_Event* e)
{
    if(e->type == SDL_EVENT_MOUSE_WHEEL)
    {
        OnMouseWheelEvent->Invoke(e);
    }
    /*if(e->key.key == -1)
        return;
    
    //if key is mod
    if(e->key.key > 0x80)
    {
        return;
    }
    prevKeys[e->key.scancode] = keys[e->key.scancode];
    switch(e->key.type)
    {
        case SDL_EVENT_KEY_DOWN:
            keys[e->key.scancode] = true;
            break;
        case SDL_EVENT_KEY_UP:
            keys[e->key.scancode] = false;
            break;
    }*/
}

bool Input::IsKeyPressed(int key)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    return SDL_GetKeyboardState(NULL)[scancode] == true;
}

bool Input::IsKeyReleased(int key)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    return SDL_GetKeyboardState(NULL)[scancode] == false;
}

glm::vec2 Input::GetMousePosition()
{
    float x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

bool Input::IsMouseButtonPressed(SDL_MouseButtonFlags button)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(button);
}

bool Input::IsMouseButtonReleased(SDL_MouseButtonFlags button)
{
    return !(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(button));
}