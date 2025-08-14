#include "Physics.h"
#include "Application.h"

//amount of physics steps each frame
int Physics::steps = 4;
std::vector<CollisionInfo*> Physics::allCollisions;

void Physics::DetectCollisions()
{
    std::vector<Collision*> collisionObjects = GetCollisionObjects();
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
                //std::cout << "Collision between: " << collisionObjects[i]->entity->GetName() << " and " << collisionObjects[j]->entity->GetName() << std::endl;
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

void Physics::ClearCollisions()
{
    allCollisions.clear();
}

std::vector<Collision*> Physics::GetCollisionObjects()
{
    std::vector<Collision*> collisionObjects;
    Entity* rootEntity = Application::Level;
    if(rootEntity == nullptr)
        return collisionObjects;
    
    AddCollisionObjects(rootEntity, collisionObjects);
    return collisionObjects;
}

void Physics::AddCollisionObjects(Entity* parent, std::vector<Collision*>& collisionObjects)
{
    std::vector children = parent->GetChildren();
    for(int i = 0; i < children.size(); i++)
    {
        std::vector<Collision*> entityCollisions = children[i]->GetComponents<Collision>();
        for(int j = 0; j < entityCollisions.size(); j++)
        {
            collisionObjects.push_back(entityCollisions[j]);
        }

        AddCollisionObjects(children[i], collisionObjects);
    }
}