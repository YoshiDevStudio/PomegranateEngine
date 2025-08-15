#include "Physics.h"
#include "Application.h"

//amount of physics steps per frame
int Physics::steps = 4;
glm::vec2 Physics::gravity = glm::vec2(0, 981.0f);

void Physics::Update()
{
    IntegrateAcceleration();
    for(int i = 0; i < steps; i++)
    {
        DetectCollisions();
        IntegrateVelocity();
    }
    ClearForces();
}

void Physics::DetectCollisions()
{
    std::vector<Collision*> collisionObjects = Application::GetAllComponentsOfType<Collision>();
    for(int i = 0; i < collisionObjects.size(); i++)
    {
        if(collisionObjects[i] == nullptr || collisionObjects[i]->entity == nullptr)
            continue;
        for(int j = i + 1; j < collisionObjects.size(); j++)
        {
            if(collisionObjects[j] == nullptr || collisionObjects[j]->entity == nullptr)
                continue;
            
            CollisionInfo info;
            if(collisionObjects[i]->CheckCollision(collisionObjects[j], info))
            {
                ImpulseResolveCollision(info.first, info.second, info.point);
                info.first->OnCollisionStay(info.second);
                info.second->OnCollisionStay(info.first);
            }
        }
    }
}

void Physics::ImpulseResolveCollision(Collision* first, Collision* second, ContactPoint& p)
{
    PhysicsBody* fBody = first->GetPhysicsBody();
    PhysicsBody* sBody = second->GetPhysicsBody();

    if(fBody == nullptr || sBody == nullptr)
        return;
    Transform2D* fTrans = first->entity->transform;
    Transform2D* sTrans = second->entity->transform;
    
    float totalMass = fBody->GetInverseMass() + sBody->GetInverseMass();
    if(totalMass == 0)
        return;
    std::cout << p.normal.x << ", " << p.normal.y << std::endl;
    if(fBody->GetInverseMass() != 0)
        fTrans->localPosition = fTrans->globalPosition - (p.normal * p.penetration * (fBody->GetInverseMass() / totalMass));
    if(sBody->GetInverseMass() != 0)
        sTrans->localPosition = sTrans->globalPosition + (p.normal * p.penetration * (sBody->GetInverseMass() / totalMass));

    glm::vec2 fFullVelocity = fBody->GetLinearVelocity();
    glm::vec2 sFullVelocity = sBody->GetLinearVelocity();
    glm::vec2 contactVelocity = sFullVelocity - fFullVelocity;
    
    float impulseForce = glm::dot(contactVelocity, p.normal);

    float cRestitution = 0.66f;
    float j = (-(1.0f + cRestitution) * impulseForce) / (totalMass);
    glm::vec2 fullImpulse = p.normal * j;

    fBody->ApplyLinearImpulse(-fullImpulse);
    sBody->ApplyLinearImpulse(fullImpulse);

}

void Physics::IntegrateAcceleration()
{
    std::vector<PhysicsBody*> bodies = Application::GetAllComponentsOfType<PhysicsBody>();
    for(int i = 0; i < bodies.size(); i++)
    {
        PhysicsBody* body = bodies[i];
        if(body == nullptr)
            continue;
        
        //Linear Motion
        float inverseMass = body->GetInverseMass();
        glm::vec2 linearVelocity = body->GetLinearVelocity();
        glm::vec2 force = body->GetForce();
        glm::vec2 accel = force * inverseMass;

        if(body->useGravity && inverseMass > 0)
        {
            accel += gravity;
        }

        linearVelocity += accel * Time::deltaTime;
        body->SetLinearVelocity(linearVelocity);

        //TODO: Angular Acceleration here
    }
}

void Physics::IntegrateVelocity()
{
    float dampingFactor = 1.0f - 0.95f;
    float frameDamping = powf(dampingFactor, Time::deltaTime);

    std::vector<PhysicsBody*> bodies = Application::GetAllComponentsOfType<PhysicsBody>();
    for(int i = 0; i < bodies.size(); i++)
    {
        PhysicsBody* body = bodies[i];
        if(body == nullptr)
            continue;
        
        Transform2D* transform = body->entity->transform;

        //Linear Motion
        glm::vec2 linearVelocity = body->GetLinearVelocity();
        transform->localPosition += linearVelocity * Time::deltaTime;

        //Linear Damping
        linearVelocity *= frameDamping;
        body->SetLinearVelocity(linearVelocity);

        //TODO: Angular Velocity here
    }
}

void Physics::ClearForces()
{
    std::vector<PhysicsBody*> bodies = Application::GetAllComponentsOfType<PhysicsBody>();
    for(int i = 0; i < bodies.size(); i++)
    {
        bodies[i]->ClearForces();
    }
}

