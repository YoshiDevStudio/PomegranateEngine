#pragma once

#include "Core.h"
#include <glm/vec2.hpp>
#include <vector>
#include "Collision.h"

struct DLL_API RaycastHit
{
    //object that was hit
    Collision* object = nullptr; 
    //hitPosition is in World Space
    glm::vec2 hitPosition;
    float rayDistance;
    //if RaycastHit hit something this will be true
    bool hit = false;
    RaycastHit()
    {
        rayDistance = FLT_MAX;
    }
};

class DLL_API Ray
{
public:
    Ray(glm::vec2 position, glm::vec2 direction, unsigned int mask = 0u)
    {
        this->position = position;
        this->direction = direction;
        this->mask = mask;
    }
    ~Ray() = default;

    glm::vec2 GetPosition() const { return position; }
    glm::vec2 GetDirection() const { return glm::normalize(direction); }
    unsigned int GetMask() const { return mask; }
private:
    glm::vec2 position;
    glm::vec2 direction;
    unsigned int mask;
};