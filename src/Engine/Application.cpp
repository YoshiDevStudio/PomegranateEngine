#include "Application.h"
#include "Camera.h"

Window* Application::window;
Entity* Application::Level;

Application::Application()
{
    window = nullptr;
    Level = new Entity("Level");
}

void Application::Run()
{
    window = new Window("SDL Game", 640, 480, SDL_WINDOW_RESIZABLE);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }
    glm::ivec2 windowSize = window->GetWindowSize();
    if (!SDL_CreateWindowAndRenderer(window->GetTitle().c_str(), windowSize.x, windowSize.y, window->GetWindowFlags(), &window->sdlWindow, &window->renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return;
    }
    this->Initialize();
    this->Start();

    bool shouldQuit = false;
    while(!shouldQuit)
    {
        SDL_Event* e;

        SDL_PollEvent(e);

        this->OnEvent(e);
        shouldQuit = window->HandleEvent(e);

        Camera* cam = Camera::currentCamera;
        if(cam != nullptr)
        {
            SDL_SetRenderLogicalPresentation(window->renderer, cam->GetSize().x, cam->GetSize().y, SDL_LOGICAL_PRESENTATION_STRETCH);
        }

        glm::vec3 clearColor = window->clearColor;
        SDL_SetRenderDrawColorFloat(window->renderer, clearColor.r, clearColor.g, clearColor.b, SDL_ALPHA_OPAQUE_FLOAT);

        SDL_RenderClear(window->renderer);

        window->FrameUpdate();
        this->Update();
        Level->Update();

        Physics::Update();

        RenderManager::Draw(window->renderer);

    #ifdef _DEBUG
        Gizmos::DrawQueued();
    #endif
        SDL_RenderPresent(window->renderer);
    }

    
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdlWindow);

    File::Uninitialize();
    
    delete Level;
    delete window;

    SDL_Quit();
}