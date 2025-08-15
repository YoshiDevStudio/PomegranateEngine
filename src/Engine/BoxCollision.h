#pragma once

#include "DLL_Build.h"
#include "Collision.h"

class DLL_API BoxCollision : public Collision
{
public:
    BoxCollision(glm::vec2 boxExtents, glm::vec2 offset = glm::vec2(0, 0))
    {
        this->boxExtents = boxExtents;
        this->offset = offset;
        this->shape = ShapeType::Box;
    }

    virtual glm::vec2 GetBroadPhaseAABBSize() override
    {
        return this->boxExtents / 2.0f;
    }

    glm::vec2 boxExtents;
};