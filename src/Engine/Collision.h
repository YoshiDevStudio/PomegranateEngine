#pragma once

#include <algorithm>
#include <glm/glm.hpp>

#include "DLL_Build.h"
#include "Transform2D.h"

class BoxCollision;
class CircleCollision;

class DLL_API Collision : public Component
{
public:
    enum ShapeType
    {
        Box,
        Circle
    } shape;

    Collision()
    {

    }
    bool IsColliding(Collision* other);


    glm::vec2 offset;
    bool isTrigger = false;

protected:
    bool IsColliding(Collision* first, Collision* second);
    bool IsColliding(BoxCollision* first, BoxCollision* second);
    bool IsColliding(CircleCollision* first, BoxCollision* second);
    bool IsColliding(CircleCollision* first, CircleCollision* second);
};