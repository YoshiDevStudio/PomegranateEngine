#include "Window.h"


SDL_Window* Window::sdlWindow;
SDL_Renderer* Window::renderer;

Window::Window(int width, int height, SDL_WindowFlags windowFlags)
{
    LOG_VERBOSE("Starting Engine");

    this->sdlWindow = nullptr;
    this->renderer = nullptr;
    this->windowRect = glm::ivec2(width, height);
    this->windowFlags = windowFlags;

    Input::Initialize();
}

Window::~Window()
{
    Input::Uninitialize();
}

//returns if quit event has occurred
bool Window::OnEvent(SDL_Event* event)
{
    if ((event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) || event->type == SDL_EVENT_QUIT) 
    {
        return true;  //end the program
    }
    Input::KeyEvent keyEvent;
    glm::ivec2 newWindowRect = this->windowRect;
    switch (event->type)
    {
    case SDL_EVENT_WINDOW_RESIZED:
        newWindowRect = glm::ivec2(event->window.data1, event->window.data2);
        this->SetWindowRect(newWindowRect);
        break;
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
    return false;
}

void Window::FrameUpdate()
{
    Time::timeElapsed = SDL_GetTicks();
    Time::deltaTime = (Time::timeElapsed - prevTime) / 1000.0f;
    prevTime = Time::timeElapsed;
}

void Window::SetWindowFlags(SDL_WindowFlags windowFlags)
{
    this->windowFlags = windowFlags;
}

SDL_WindowFlags Window::GetWindowFlags()
{
    return this->windowFlags;
}

void Window::SetWindowRect(glm::ivec2 rect)
{
    this->windowRect = rect;
}

void Window::SetWindowRect(int width, int height)
{
    this->windowRect = glm::ivec2(width, height);
}

glm::ivec2 Window::GetWindowRect()
{
    return this->windowRect;
}
