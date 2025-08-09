#include <Engine.h>

class Game : public Application
{
public:
    Game()
        : Application()
    {
        
    }

    ~Game() = default;
};

Application* CreateApplication()
{
    return new Game();
}