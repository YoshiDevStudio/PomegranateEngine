#include "Window.h"


Window::Window(SDL_Window* window, SDL_Renderer* renderer)
{
    this->Initialize(window, renderer);
}

Window::~Window()
{
    this->Uninitialize();
}

void Window::Initialize(SDL_Window* window, SDL_Renderer* renderer)
{
    LOG_VERBOSE("Starting Engine");

    this->sdlWindow = window;
    this->renderer = renderer;
    Input::Initialize();
}

void Window::Uninitialize()
{
    Input::Uninitialize();
}

SDL_AppResult Window::OnEvent(SDL_Event* event)
{
    if ((event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) || event->type == SDL_EVENT_QUIT) 
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    Input::KeyEvent keyEvent;
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        break;
    case SDL_EVENT_KEY_DOWN:
        keyEvent = Input::KeyEvent(event->key.key, Input::KeyEventType::KeyDown, event->key.mod);
        Input::OnKeyEvent(keyEvent);
        break;
    case SDL_EVENT_KEY_UP:
        keyEvent = Input::KeyEvent(event->key.key, Input::KeyEventType::KeyUp, event->key.mod);
        Input::OnKeyEvent(keyEvent);
        break;
    }
    return SDL_APP_CONTINUE;
}

void Window::FrameUpdate()
{
    Time::timeElapsed = SDL_GetTicks();
    Time::deltaTime = Time::timeElapsed - prevTime;
    prevTime = Time::timeElapsed;
}
