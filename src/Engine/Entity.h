#pragma once

#include "Core.h"
#include <string>
#include <vector>

class Component;
class Transform2D;

//Entity is freed by engine as long as its a child under Application::Level
class DLL_API Entity
{
public:
    Entity();
    Entity(std::string name);
    Entity(std::string name, Component* component);
    
    ~Entity();

    void Destroy();

    virtual void Initialize();
    virtual void Start();
    virtual void Update();

    bool AddChild(Entity* child);
    bool RemoveChild(Entity* child);
    Entity* GetChild(std::string name);
    Entity* GetChildByIndex(int index);
    std::vector<Entity*> GetChildren();
    Entity* GetRootEntity();
    std::string GetPath();
    
    void SetParent(Entity* parent);
    Entity* GetParent();
    void SetName(std::string name);
    std::string GetName();

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    //returns first component of type T on entity
    //returns nullptr if component was not found
    template <typename T>
    T* GetComponent()
    {
        for(int i = 0; i < components.size(); i++)
        {
            //If components[i] is of type T
            if(dynamic_cast<T*>(components[i]) != nullptr)
            {
                return dynamic_cast<T*>(components[i]);
            }
        }
        return nullptr;
    }

    //returns all components of type T on entity
    //returns nullptr if component was not found
    template <typename T>
    std::vector<T*> GetComponents()
    {
        std::vector<T*> c;
        for(int i = 0; i < components.size(); i++)
        {
            //If components[i] is of type T
            if(dynamic_cast<T*>(components[i]) != nullptr)
            {
                c.push_back((T*)components[i]);
            }
        }
        return c;
    }
    
    Transform2D* transform = nullptr;
private:
    std::string name;
    std::vector<Entity*> children;
    Entity* parent = nullptr;

    std::vector<Component*> components;
};