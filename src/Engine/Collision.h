#pragma once

#include <algorithm>
#include <glm/glm.hpp>

#include "DLL_Build.h"
#include "Transform2D.h"

class BoxCollision;
class CircleCollision;
class Collision;

struct DLL_API ContactPoint
{
    //where the collision occured on each object
    glm::vec2 a, b; 
    glm::vec2 normal;
    float penetration;
};

struct DLL_API CollisionInfo
{
    Collision* first;
    Collision* second;
    ContactPoint point;

    int framesLeft;
    void AddContactPoint(glm::vec2& a, glm::vec2& b, glm::vec2& normal, float penetration)
    {
        point.a = a;
        point.b = b;
        point.normal = normal;
        point.penetration = penetration;
    }
};

//Collision sizes are unaffected by Entitys scale
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
    void CollisionEnter(CollisionInfo* info);
    void CollisionExit(CollisionInfo* info);

    bool CheckCollision(Collision* other, CollisionInfo& collisionInfo);

    glm::vec2 offset;
    //determines if other collision objects will be able to walk through this collision object
    bool isTrigger = false;

    //determines if the entity this collision is attached to will get pushed when colliding with other objects
    bool isStatic = true;

private:
    bool CheckCollision(Collision* first, Collision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(BoxCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, CircleCollision* second, CollisionInfo& collisionInfo);
};