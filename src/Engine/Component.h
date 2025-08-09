#pragma once

#include "Entity.h"

//Declare that entity exists since its a cyclical dependency
class Entity;

class DLL_API Component
{
public:
    Component()
    {
        Initialize();
    }
    virtual ~Component() = default;

    virtual void Initialize()
    {
        Start();
    }
    virtual void Start()
    {

    }
    virtual void Update()
    {
        
    }

    Entity* entity = nullptr;
};