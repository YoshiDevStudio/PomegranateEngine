#pragma once

#include "Transform2D.h"
#include "Collision.h"
#include "PhysicsBody.h"

class Application;

//TODO: Implement Angular Motion
class DLL_API Physics
{
public:
    static void Update();

    static int steps;
    static glm::vec2 gravity;
private:
    //Collisions
    static void DetectCollisions();
    static void ImpulseResolveCollision(Collision* first, Collision* second, ContactPoint& p);
    //Linear Motion
    static void IntegrateAcceleration();
    static void IntegrateVelocity();

    static void ClearForces();
};