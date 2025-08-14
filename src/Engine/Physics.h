#pragma once

#include "Collision.h"

class Application;

class DLL_API Physics
{
public:
    static void DetectCollisions();
    static void ResolveCollisions();
    static void ClearCollisions();

    static int steps;
private:
    static std::vector<Collision*> GetCollisionObjects();
    static void AddCollisionObjects(Entity* parent, std::vector<Collision*>& collisionObjects);

    static std::vector<CollisionInfo*> allCollisions;
};