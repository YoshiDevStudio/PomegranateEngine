#include "Window.h"


SDL_Window* Window::sdlWindow;
SDL_Renderer* Window::renderer;

Window::Window(std::string title, int width, int height, SDL_WindowFlags windowFlags)
{
    LOG_VERBOSE("Starting Engine");

    this->sdlWindow = nullptr;
    this->renderer = nullptr;
    this->title = title;
    this->windowRect = glm::ivec2(width, height);
    this->windowFlags = windowFlags;

    Input::Initialize();
}

Window::~Window()
{
    Input::Uninitialize();
}

//returns if quit event has occurred
bool Window::HandleEvent(SDL_Event* event)
{
    if ((event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) || event->type == SDL_EVENT_QUIT) 
    {
        return true;  //end the program
    }
    glm::ivec2 newWindowRect = this->windowRect;
    switch (event->type)
    {
    case SDL_EVENT_WINDOW_RESIZED:
        newWindowRect = glm::ivec2(event->window.data1, event->window.data2);
        this->SetWindowRect(newWindowRect);
        break;
    default:
        Input::OnEvent(event);
        break;
    }
    return false;
}

void Window::FrameUpdate()
{
    Time::timeElapsed = SDL_GetTicks() / 1000.0f;
    Time::deltaTime = (Time::timeElapsed - prevTime);
    prevTime = Time::timeElapsed;
}

void Window::SetTitle(std::string title)
{
    if(SDL_SetWindowTitle(sdlWindow, title.c_str()))
        this->title = title;
}

std::string Window::GetTitle()
{
    return this->title;
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

void Window::SetWindowResizable(bool isResizable)
{
    SDL_SetWindowResizable(sdlWindow, isResizable);
}

void Window::SetWindowFullscreen(bool isFullscreen)
{
    SDL_SetWindowFullscreen(sdlWindow, isFullscreen);
}
