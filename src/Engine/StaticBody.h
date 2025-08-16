#pragma once

#include "Core.h"
#include "PhysicsBody.h"

class DLL_API StaticBody : public PhysicsBody
{
public:
    StaticBody();

    virtual float GetInverseMass() override;
};