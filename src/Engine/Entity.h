#pragma once

#include "Engine.h"
#include "Component.h"
#include "Transform2D.h"

//Cyclically Dependent so these have to be declared to compile
class Component;
class Transform2D;

class Entity
{
public:
    Entity();
    Entity(std::string name);
    ~Entity();

    virtual void Initialize();
    virtual void Start();
    virtual void Update();

    bool AddChild(Entity* child);
    bool RemoveChild(Entity* child);
    Entity* GetChild(std::string name);
    Entity* GetChildByIndex(int index);
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
            if(typeid(T*).hash_code() == typeid(components[i]).hash_code())
            {
                return components[i];
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
            if(typeid(T*).hash_code() == typeid(components[i]).hash_code())
            {
                c.push_back(components[i]);
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