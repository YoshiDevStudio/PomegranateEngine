#include "Application.h"

Window* Application::window;
Entity* Application::Level;

Application::Application()
{
    window = nullptr;
    Level = new Entity("Level");
}

Application::~Application()
{

}

void Application::Initialize()
{
    
}

void Application::Start()
{
    
}

void Application::OnEvent(SDL_Event* event)
{

}

void Application::Update()
{

}

void Application::Run()
{
    window = new Window("SDL Game", 640, 480, SDL_WINDOW_RESIZABLE);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }
    glm::ivec2 windowRect = window->GetWindowRect();
    if (!SDL_CreateWindowAndRenderer(window->GetTitle().c_str(), windowRect.x, windowRect.y, window->GetWindowFlags(), &window->sdlWindow, &window->renderer))
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

        const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
        /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
        const float red = (float) (0.5 + 0.5 * SDL_sin(now));
        const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
        SDL_SetRenderDrawColorFloat(window->renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

        SDL_RenderClear(window->renderer);

        window->FrameUpdate();
        this->Update();
        Level->Update();

        RenderManager::Draw(window->renderer);

        SDL_SetRenderDrawColorFloat(window->renderer, 1.0, 1.0, 1.0, 1.0);
        SDL_RenderDebugText(window->renderer, 640 / 2, 480 / 2, std::to_string(Time::deltaTime).append("ms").c_str());

        SDL_RenderPresent(window->renderer);
    }

    
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdlWindow);

    File::Uninitialize();
    
    delete Level;
    delete window;

    SDL_Quit();
}