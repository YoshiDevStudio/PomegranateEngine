#pragma once

#include "Core.h"
#include "Collision.h"
#ifdef _DEBUG
    #include "Gizmos.h"
#endif

class DLL_API BoxCollision : public Collision
{
public:
    BoxCollision(glm::vec2 boxExtents, glm::vec2 offset = glm::vec2(0, 0))
    {
        this->boxExtents = boxExtents;
        this->offset = offset;
        this->shape = ShapeType::Box;
    }
#ifdef _DEBUG
    virtual void Update() override
    {
        glm::vec2 pos;
        if(entity == nullptr)
            pos = offset;
        else
            pos = entity->transform->globalPosition + offset;
        Gizmos::DrawRect(pos - (boxExtents * 0.5f), boxExtents, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }
#endif

    virtual glm::vec2 GetBroadPhaseAABBSize() override
    {
        return this->boxExtents / 2.0f;
    }

    glm::vec2 boxExtents;
};