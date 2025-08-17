#include "Input.h"
#include "Camera.h"
#include "Application.h"

Event<void, SDL_Event*>* Input::OnMouseWheelEvent;
//Constructor
void Input::Initialize()
{
    //For some reason the compiler screams at me when I try to delete this or when its not a pointer so it shall stay as is
    OnMouseWheelEvent = new Event<void, SDL_Event*>();
}

//Deconstructor
void Input::Uninitialize()
{
    
}

void Input::OnEvent(SDL_Event* e)
{
    if(e->type == SDL_EVENT_MOUSE_WHEEL)
    {
        OnMouseWheelEvent->Invoke(e);
    }
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

glm::vec2 Input::GetScreenMousePosition()
{
    float x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

glm::vec2 Input::GetWorldMousePosition()
{
    glm::vec2 screenPos = GetScreenMousePosition();
    Camera* cam = Camera::currentCamera;
    if(cam != nullptr)
    {
        glm::vec2 camSize = cam->GetSize();
        glm::vec2 windowSize = Application::window->GetWindowSize();
        
        screenPos *= (camSize / windowSize);
        return screenPos + cam->GetCenterPos();
    }
    return screenPos;
}

bool Input::IsMouseButtonPressed(SDL_MouseButtonFlags button)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(button);
}

bool Input::IsMouseButtonReleased(SDL_MouseButtonFlags button)
{
    return !(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MASK(button));
}