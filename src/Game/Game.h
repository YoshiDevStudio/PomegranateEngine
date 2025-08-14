#pragma once

#include <Engine.h>

class Game : public Application
{
public:
    void Start() override;
    void Update() override;
};

Application* CreateApplication()
{
    return new Game();
}
