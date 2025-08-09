#include "Application.h"

Window* Application::window;

Application::Application()
{
    window = nullptr;
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
    window = new Window(640, 480, SDL_WINDOW_RESIZABLE);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }
    glm::ivec2 windowRect = window->GetWindowRect();
    if (!SDL_CreateWindowAndRenderer("SDL Game", windowRect.x, windowRect.y, window->GetWindowFlags(), &window->sdlWindow, &window->renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return;
    }
    this->Initialize();

    //File::LoadPNGInFolder("textures");

    //Load Level
    //!!TODO: Load from File
    level = new Entity("Level");

    //std::cout << Time::GetLocalTimeMS() << std::endl;

    //For testing
    /*Entity* child1 = new Entity("child1");
    Entity* a1 = new Entity("a1");
    Entity* a2 = new Entity("a2");
    level->AddChild(child1);

    child1->AddChild(a1);
    child1->AddChild(a2);

    Entity* child2 = new Entity("child2");
    Entity* b1 = new Entity("b1");
    Entity* b2 = new Entity("b2");

    level->AddChild(child2);
    
    child2->AddChild(b1);
    child2->AddChild(b2);

    std::cout << level->GetChild(b2->GetPath())->GetName() << std::endl;
    std::cout << child1->GetChildByIndex(0)->GetName() << std::endl;
    std::cout << b2->GetPath() << std::endl;*/
    this->Start();

    bool shouldQuit = false;

    while(!shouldQuit)
    {
        SDL_Event* e;

        SDL_PollEvent(e);

        this->OnEvent(e);
        shouldQuit = window->OnEvent(e);

        window->FrameUpdate();
        this->Update();
        level->Update();
        const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
        /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
        const float red = (float) (0.5 + 0.5 * SDL_sin(now));
        const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
        SDL_SetRenderDrawColorFloat(window->renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

        SDL_RenderClear(window->renderer);

        SDL_SetRenderDrawColorFloat(window->renderer, 1.0, 1.0, 1.0, 1.0);
        SDL_RenderDebugText(window->renderer, 640 / 2, 480 / 2, std::to_string(Time::deltaTime).append("ms").c_str());

        SDL_RenderPresent(window->renderer);
    }

    
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdlWindow);

    delete level;
    delete window;

    SDL_Quit();
}