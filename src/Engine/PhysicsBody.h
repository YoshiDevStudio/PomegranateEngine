#pragma once

#include "Core.h"

#include "Transform2D.h"
#include "Collision.h"

class DLL_API PhysicsBody : public Component
{
public:
    PhysicsBody(float mass = 1.0f, bool useGravity = false);

    virtual void OnAttach() override;

    void AddForce(glm::vec2& force);
    void ClearForces();

    void ApplyLinearImpulse(glm::vec2 force);

    void SetMass(float mass);
    void SetLinearVelocity(glm::vec2 linearVelocity);
    void SetForce(glm::vec2 force);
    void SetLinearDamping(float linearDamping);

    virtual float GetInverseMass();
    glm::vec2 GetLinearVelocity();
    glm::vec2 GetForce();
    float GetLinearDamping();

    bool useGravity;
    Collision* collision = nullptr;
protected:
    float inverseMass = 1.0f;
    glm::vec2 linearVelocity;
    glm::vec2 force;
    float linearDamping = 0.05f;
};