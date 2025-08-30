#pragma once

#include <Engine.h>

//Game is a placeholder name and can be changed to anything you want as long as it inherits from Application
class Game : public Application
{
public:
    void Start() override;
    void Update() override;
};

//This function needs to exist to connect to the Engine
Application* CreateApplication()
{
    return new Game();
}
