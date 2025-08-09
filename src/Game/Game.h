#pragma once

#include <Engine.h>

class Game : public Application
{
public:
    Game() : Application() {}
    ~Game() = default;

    void Start() override;
    void Update() override;
};

Application* CreateApplication()
{
    return new Game();
}
