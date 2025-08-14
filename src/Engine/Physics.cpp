#include "Physics.h"
#include "Application.h"

//amount of physics steps each frame
int Physics::steps = 4;
glm::vec2 Physics::gravity = glm::vec2(0, 981.0f);

std::vector<CollisionInfo*> Physics::allCollisions;

void Physics::Update()
{
    IntegrateAcceleration();
    IntegrateVelocity();
    DetectCollisions();

    for(int i = 0; i < steps; i++)
    {
        ResolveCollisions();
    }
    allCollisions.clear();
}

void Physics::DetectCollisions()
{
    std::vector<Collision*> collisionObjects = Application::GetAllComponentsOfType<Collision>();
    std::vector<CollisionInfo> collisions;
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
                info.framesLeft = steps;
                allCollisions.push_back(&info);
            }
        }
    }
}

void Physics::ResolveCollisions()
{
    for(int i = 0; i < allCollisions.size(); i++)
    {
        CollisionInfo* currentInfo = allCollisions[i];
        if(currentInfo->first == nullptr || currentInfo->second == nullptr)
            continue;

        if(currentInfo->framesLeft == steps)
        {
            currentInfo->first->CollisionEnter(currentInfo);
            currentInfo->second->CollisionEnter(currentInfo);
        }
        currentInfo->framesLeft -= 1;
        if(currentInfo->framesLeft <= 0)
        {
            currentInfo->first->CollisionExit(currentInfo);
            currentInfo->second->CollisionExit(currentInfo);
            allCollisions.erase(allCollisions.begin() + i);
        }
    }
}

void Physics::IntegrateAcceleration()
{
    std::vector<PhysicsBody*> bodies = Application::GetAllComponentsOfType<PhysicsBody>();
    for(int i = 0; i < bodies.size(); i++)
    {
        PhysicsBody* body = bodies[i];
        if(body == nullptr)
            continue;
        
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

        glm::vec2 linearVelocity = body->GetLinearVelocity();
        transform->localPosition += linearVelocity * Time::deltaTime;

        //Linear Damping
        linearVelocity *= frameDamping;
        body->SetLinearVelocity(linearVelocity);
    }
}
