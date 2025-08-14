#pragma once

#include "Transform2D.h"
#include "Collision.h"
#include "PhysicsBody.h"

class Application;

class DLL_API Physics
{
public:
    static void Update();

    static int steps;
    static glm::vec2 gravity;
private:
    //Collisions
    static void DetectCollisions();
    static void ResolveCollisions();
    //Linear Motion
    static void IntegrateAcceleration();
    static void IntegrateVelocity();

    static std::vector<CollisionInfo*> allCollisions;
};