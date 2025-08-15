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
    bool operator < (const CollisionInfo& other) const 
    {
        //this operator is necessary for QuadTrees to operate
        size_t otherHash = (size_t)other.first + ((size_t)other.second << 8);
        size_t thisHash = (size_t)first + ((size_t)second << 8);

        return (thisHash < otherHash);
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
    static bool AABBTest(glm::vec2 fPos, glm::vec2 sPos, glm::vec2 fSize, glm::vec2 sSize);

    virtual glm::vec2 GetBroadPhaseAABBSize() = 0;

    glm::vec2 GetGlobalPosition();
    PhysicsBody* GetPhysicsBody();

    glm::vec2 offset = glm::vec2(0, 0);
    //determines if other collision objects will be able to walk through this collision object
    bool isTrigger = false;
    PhysicsBody* body = nullptr;
private:
    bool CheckCollision(Collision* first, Collision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(BoxCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, BoxCollision* second, CollisionInfo& collisionInfo);
    bool CheckCollision(CircleCollision* first, CircleCollision* second, CollisionInfo& collisionInfo);
};