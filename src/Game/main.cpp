
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <Engine.h>

static SDL_Window* sdlWindow = NULL;
static SDL_Renderer* renderer = NULL;
static Window* window = NULL;

Entity* level = nullptr;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    window = new Window(640, 480, sdlWindow, renderer);
    window->SetWindowFlags(SDL_WINDOW_RESIZABLE);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    glm::ivec2 windowRect = window->GetWindowRect();
    if (!SDL_CreateWindowAndRenderer("SDL Game", windowRect.x, windowRect.y, window->GetWindowFlags(), &sdlWindow, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

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

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return window->OnEvent(event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    window->FrameUpdate();
    level->Update();
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColorFloat(renderer, 1.0, 1.0, 1.0, 1.0);
    SDL_RenderDebugText(renderer, 640 / 2, 480 / 2, std::to_string(Time::deltaTime).append("ms").c_str());

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    delete level;
    delete window;
}