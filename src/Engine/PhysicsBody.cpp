#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float mass, bool useGravity)
{
    SetMass(mass);
    this->useGravity = useGravity;
}

void PhysicsBody::AddForce(glm::vec2& force)
{
    this->force += force;
}

void PhysicsBody::ClearForces()
{
    force = glm::vec2(0, 0);
}

void PhysicsBody::SetMass(float mass)
{
    this->inverseMass = 1 / mass;
}

void PhysicsBody::SetLinearVelocity(glm::vec2 linearVelocity)
{
    this->linearVelocity = linearVelocity;
}

void PhysicsBody::SetForce(glm::vec2 force)
{
    this->force = force;
}

float PhysicsBody::GetInverseMass()
{
    return this->inverseMass;
}

glm::vec2 PhysicsBody::GetLinearVelocity()
{
    return linearVelocity;
}

glm::vec2 PhysicsBody::GetForce()
{
    return this->force;
}

