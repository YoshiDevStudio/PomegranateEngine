#pragma once

#include "Engine.h"
#include "Component.h"

class Entity
{
public:
    Entity();
    Entity(std::string name);
    ~Entity();

    void Initialize();
    void Start();
    void Update();

    bool AddChild(Entity* child);
    bool RemoveChild(Entity* child);
    Entity* GetChild(std::string name);
    Entity* GetChildByIndex(int index);
    int GetChildIndex();
    Entity* GetRootEntity();
    std::string GetPath();
    
    void SetParent(Entity* parent);
    void SetName(std::string name);
    std::string GetName();

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    
private:
    std::string name;
    std::vector<Entity*> children;
    Entity* parent = nullptr;

    std::vector<Component*> components;

    //parent->children[childIndex] = this
    //if parent is null childIndex = -1
    int childIndex;
    Entity* rootEntity = nullptr;
};