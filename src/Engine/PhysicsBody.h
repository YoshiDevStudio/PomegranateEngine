#pragma once

#include "DLL_Build.h"

#include "Transform2D.h"
#include "Collision.h"

class DLL_API PhysicsBody : public Component
{
public:
    PhysicsBody(float mass = 1, bool useGravity = false);

    void AddForce(glm::vec2& force);
    void ClearForces();

    void SetMass(float mass);
    void SetLinearVelocity(glm::vec2 linearVelocity);
    void SetForce(glm::vec2 force);

    float GetInverseMass();
    glm::vec2 GetLinearVelocity();
    glm::vec2 GetForce();

    bool useGravity;
protected:
    Collision* collision;

    float inverseMass;
    glm::vec2 linearVelocity;
    glm::vec2 force;
};