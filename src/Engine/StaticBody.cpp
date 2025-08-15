#include "StaticBody.h"

StaticBody::StaticBody()
{
    this->inverseMass = 0.0f;
    this->useGravity = false;
}

void StaticBody::AddForce(glm::vec2& force)
{
    return;
}

void StaticBody::ApplyLinearImpulse(glm::vec2 force)
{
    return;
}

void StaticBody::SetMass(float mass)
{
    return;
}

void StaticBody::SetLinearVelocity(glm::vec2 linearVelocity)
{
    return;
}

void StaticBody::SetForce(glm::vec2 force)
{
    return;
}

float StaticBody::GetInverseMass()
{
    return 0.0f;
}