#pragma once

#include "Core.h"
#include "PhysicsBody.h"

class DLL_API StaticBody : public PhysicsBody
{
public:
    StaticBody()
    {
        this->inverseMass = 0.0f;
    }

    virtual float GetInverseMass() override
    {
        return 0.0f;
    }
};