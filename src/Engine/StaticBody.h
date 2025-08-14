#pragma once

#include "DLL_Build.h"
#include "PhysicsBody.h"

class DLL_API StaticBody : public PhysicsBody
{
public:
    StaticBody();

    virtual void AddForce(glm::vec2& force) override;

    virtual void ApplyLinearImpulse(glm::vec2 force) override;

    virtual void SetMass(float mass) override;
    virtual void SetLinearVelocity(glm::vec2 linearVelocity) override;
    virtual void SetForce(glm::vec2 force) override;

    virtual float GetInverseMass() override;
};