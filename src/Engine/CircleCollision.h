#pragma once

#include "DLL_Build.h"
#include "Collision.h"
#ifdef _DEBUG
    #include "Gizmos.h"
#endif

class DLL_API CircleCollision : public Collision
{
public:
    CircleCollision(float radius, glm::vec2 offset = glm::vec2(0, 0))
    {
        this->radius = radius;
        this->offset = offset;
        this->shape = ShapeType::Circle;
    }
#ifdef _DEBUG
    virtual void Update() override
    {
        glm::vec2 pos;
        if(entity == nullptr)
            pos = offset;
        else
            pos = entity->transform->globalPosition + offset;
        Gizmos::DrawCircle(pos, radius, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }
#endif

    virtual glm::vec2 GetBroadPhaseAABBSize() override
    {
        return glm::vec2(radius, radius);
    }

    float radius;
};