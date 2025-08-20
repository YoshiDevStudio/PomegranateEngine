#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(float mass, bool useGravity)
{
    this->inverseMass = 1.0f / mass;
    this->useGravity = useGravity;
}

void PhysicsBody::OnAttach()
{
    collision = entity->GetComponent<Collision>();
    if(collision != nullptr)
        collision->body = this;
}

void PhysicsBody::AddForce(glm::vec2& force)
{
    this->force += force;
}

void PhysicsBody::ClearForces()
{
    force = glm::vec2(0, 0);
}

void PhysicsBody::ApplyLinearImpulse(glm::vec2 force)
{
    linearVelocity += force * inverseMass;
}

void PhysicsBody::SetMass(float mass)
{
    if(mass == 0)
    {
        LOG_ERROR("mass cannot be 0 on PhysicsBody, Consider using a StaticBody");
        return;
    }
    this->inverseMass = 1.0f / mass;
}

void PhysicsBody::SetLinearVelocity(glm::vec2 linearVelocity)
{
    this->linearVelocity = linearVelocity;
}

void PhysicsBody::SetForce(glm::vec2 force)
{
    this->force = force;
}

void PhysicsBody::SetLinearDamping(float linearDamping)
{
    this->linearDamping = linearDamping;
}

float PhysicsBody::GetInverseMass()
{
    return inverseMass;
}

glm::vec2 PhysicsBody::GetLinearVelocity()
{
    return linearVelocity;
}

glm::vec2 PhysicsBody::GetForce()
{
    return this->force;
}

float PhysicsBody::GetLinearDamping()
{
    return this->linearDamping;
}

