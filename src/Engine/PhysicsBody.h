#pragma once

#include "DLL_Build.h"

#include "Transform2D.h"
#include "Collision.h"

class DLL_API PhysicsBody : public Component
{
public:
    PhysicsBody(float mass = 1.0f, bool useGravity = false);

    virtual void OnAttach() override;

    virtual void AddForce(glm::vec2& force);
    void ClearForces();

    virtual void ApplyLinearImpulse(glm::vec2 force);

    virtual void SetMass(float mass);
    virtual void SetLinearVelocity(glm::vec2 linearVelocity);
    virtual void SetForce(glm::vec2 force);

    virtual float GetInverseMass();
    glm::vec2 GetLinearVelocity();
    glm::vec2 GetForce();

    bool useGravity;
    Collision* collision = nullptr;
protected:
    float inverseMass = 1.0f;
    glm::vec2 linearVelocity;
    glm::vec2 force;
};