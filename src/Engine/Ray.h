#pragma once

#include "Core.h"
#include <glm/vec2.hpp>
#include <vector>
#include "Collision.h"

struct DLL_API RaycastHit
{
    //object that was hit
    Collision* object; 
    //hitPosition is in World Space
    glm::vec2 hitPosition;
    float rayDistance;
    RaycastHit()
    {
        rayDistance = -1.0f;
    }
};

class DLL_API Ray
{
public:
    Ray(glm::vec2 position, glm::vec2 direction, unsigned int layer = 0)
    {
        this->position = position;
        this->direction = direction;
        this->layer = layer;
    }
    ~Ray() = default;

    glm::vec2 GetPosition() const { return position; }
    glm::vec2 GetDirection() const { return glm::normalize(direction); }
    unsigned int GetLayer() const { return layer; }
private:
    glm::vec2 position;
    glm::vec2 direction;
    unsigned int layer = 0;
};