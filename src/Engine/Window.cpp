#include "Window.h"


SDL_Window* Window::sdlWindow;
SDL_Renderer* Window::renderer;

Window::Window(std::string title, int width, int height, SDL_WindowFlags windowFlags)
{
    LOG_VERBOSE("Starting Engine");

    this->sdlWindow = nullptr;
    this->renderer = nullptr;
    this->title = title;
    this->windowSize = glm::ivec2(width, height);
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
    glm::ivec2 newWindowSize = this->windowSize;
    switch (event->type)
    {
    case SDL_EVENT_WINDOW_RESIZED:
        newWindowSize = glm::ivec2(event->window.data1, event->window.data2);
        this->SetWindowSize(newWindowSize);
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

void Window::SetWindowSize(glm::ivec2 rect)
{
    this->windowSize = rect;
}

void Window::SetWindowSize(int width, int height)
{
    this->windowSize = glm::ivec2(width, height);
}

glm::ivec2 Window::GetWindowSize()
{
    return this->windowSize;
}

void Window::SetWindowResizable(bool isResizable)
{
    SDL_SetWindowResizable(sdlWindow, isResizable);
}

void Window::SetWindowFullscreen(bool isFullscreen)
{
    SDL_SetWindowFullscreen(sdlWindow, isFullscreen);
}
