#pragma once

#include <set>
#include <algorithm>
#include "Transform2D.h"
#include "Collision.h"
#include "PhysicsBody.h"
#include "QuadTree.h"
#include "Ray.h"
#ifdef _DEBUG
    #include "Gizmos.h"
#endif

class Application;

//TODO: Implement Angular Motion
class DLL_API Physics
{
public:
    static void Update();
    static bool Raycast(Ray& ray, RaycastHit& hitInfo);

    static int steps;
    static glm::vec2 gravity;
    static bool useQuadTrees;
private:
    //Quadtree Phases
    static void BroadPhase();
    static void NarrowPhase();
    //Collisions
    static void DetectCollisions();
    static void ImpulseResolveCollision(Collision* first, Collision* second, ContactPoint& p);
    //Linear Motion
    static void IntegrateAcceleration();
    static void IntegrateVelocity();

    static void ClearForces();

    static std::set<CollisionInfo> broadPhaseCollisions;
};