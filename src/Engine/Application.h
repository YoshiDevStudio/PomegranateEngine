#pragma once

#include "Core.h"
#include "Window.h"
#include "Physics.h"
#include "RenderManager.h"
#include "File.h"

class DLL_API Application
{
public:
    Application();
    virtual ~Application() = default;

    virtual void Initialize() {}
    virtual void Start() {}
    virtual void OnEvent(SDL_Event* event) {}
    virtual void Update() {}
    
    //Should only be called by Engine in EntryPoint.h
    void Run();

    template <typename T>
    static std::vector<T*> GetAllComponentsOfType()
    {
        std::vector<T*> components;
        Entity* rootEntity = Application::Level;
        if(rootEntity == nullptr)
            return components;
        
        AddComponentObjects(rootEntity, components);
        return components;
    }

    static Window* window;
    static Entity* Level;
private:
    template <typename T>
    static void AddComponentObjects(Entity* parent, std::vector<T*>& components)
    {
        std::vector children = parent->GetChildren();
        for(int i = 0; i < children.size(); i++)
        {
            std::vector<T*> entityComponents = children[i]->GetComponents<T>();
            for(int j = 0; j < entityComponents.size(); j++)
            {
                if(entityComponents[j]->enabled)
                    components.push_back(entityComponents[j]);
            }

            AddComponentObjects(children[i], components);
        }
    }
};
//must be defined in .exe
Application* CreateApplication();
