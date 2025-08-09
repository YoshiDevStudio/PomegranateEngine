#pragma once

#include "Core.h"
#include "Window.h"

class Window;

class DLL_API Application
{
public:
    Application();
    virtual ~Application();

    virtual void Initialize();
    virtual void Start();
    virtual void OnEvent(SDL_Event* event);
    virtual void Update();

    void Run();

    static Window* window;
    Entity* level = nullptr;
};
//must be defined in .exe
Application* CreateApplication();
