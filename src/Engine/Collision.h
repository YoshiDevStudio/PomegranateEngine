#pragma once

#include <algorithm>
#include <glm/glm.hpp>

#include "DLL_Build.h"
#include "Transform2D.h"

class BoxCollision;
class CircleCollision;
class Collision;
class PhysicsBody;

struct DLL_API ContactPoint
{
    //where the collision occured on each object
    glm::vec2 a, b; 
    glm::vec2 normal;
    float penetration;
};

struct DLL_API CollisionInfo
{
    Collision* first = nullptr;
    Collision* second = nullptr;
    ContactPoint point;

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
    virtual void OnAttach() override;

    void OnCollisionStay(Collision* info);

    bool CheckCollision(Collision* other, CollisionInfo& collisionInfo);

    PhysicsBody* GetPhysicsBody();

    glm::vec2 offset;
    //determines if other collision objects will be able to walk through this collision object
    bool isTrigger = false;
    PhysicsBody* body = nullptr;
private:
    bool CheckCollision(Collision* first, Collision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(BoxCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, CircleCollision* second, CollisionInfo& collisionInfo);
};