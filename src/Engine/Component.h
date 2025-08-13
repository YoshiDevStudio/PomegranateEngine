#pragma once

#include "Entity.h"

class DLL_API Component
{
public:
    Component()
    {
        Initialize();
    }
    virtual ~Component() = default;


    virtual void OnAttach()
    {

    }
    virtual void OnDeAttach()
    {
        
    }
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