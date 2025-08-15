#pragma once

#include "DLL_Build.h"
#include "Collision.h"

class DLL_API CircleCollision : public Collision
{
public:
    CircleCollision(float radius, glm::vec2 offset = glm::vec2(0, 0))
    {
        this->radius = radius;
        this->offset = offset;
        this->shape = ShapeType::Circle;
    }

    virtual glm::vec2 GetBroadPhaseAABBSize() override
    {
        return glm::vec2(radius, radius);
    }

    float radius;
};