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
    
    //Should only be called by Engine in EntryPoint.h
    void Run();

    static Window* window;
    static Entity* Level;
private:
};
//must be defined in .exe
Application* CreateApplication();
