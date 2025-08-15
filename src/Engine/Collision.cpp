#include "Collision.h"
#include "BoxCollision.h"
#include "CircleCollision.h"
#include "PhysicsBody.h"

void Collision::OnAttach()
{
    body = entity->GetComponent<PhysicsBody>();
    if(body != nullptr)
        body->collision = this;
}

void Collision::OnCollisionStay(Collision* other)
{
    //std::cout << "On Collision" << std::endl;
}


bool Collision::CheckCollision(Collision* other, CollisionInfo& collisionInfo)
{
    if(this->entity == nullptr || other->entity == nullptr)
        return false;
    return CheckCollision(this, other, collisionInfo);
}

PhysicsBody* Collision::GetPhysicsBody()
{
    if(body == nullptr)
        body = entity->GetComponent<PhysicsBody>();
    return body;
}

bool Collision::CheckCollision(Collision* first, Collision* second, CollisionInfo& collisionInfo)
{
    switch(first->shape)
    {
        case ShapeType::Box:
        switch(second->shape)
        {
            case ShapeType::Box:
                return Collision::CheckCollision(dynamic_cast<BoxCollision*>(first), dynamic_cast<BoxCollision*>(second), collisionInfo);
                break;
            case ShapeType::Circle:
                return Collision::CheckCollision(dynamic_cast<CircleCollision*>(second), dynamic_cast<BoxCollision*>(first), collisionInfo);
                break;
        }
        break;
        case ShapeType::Circle:
        switch(second->shape)
        {
            case ShapeType::Box:
                return Collision::CheckCollision(dynamic_cast<CircleCollision*>(first), dynamic_cast<BoxCollision*>(second), collisionInfo);
                break;
            case ShapeType::Circle:
                return Collision::CheckCollision(dynamic_cast<CircleCollision*>(second), dynamic_cast<CircleCollision*>(first), collisionInfo);
                break;
        }
        break;
    }
    return false;
}

bool Collision::CheckCollision(BoxCollision* first, BoxCollision* second, CollisionInfo& collisionInfo)
{
    glm::vec2 fPos = first->entity->transform->globalPosition;
    glm::vec2 sPos = second->entity->transform->globalPosition;

    glm::vec2 fHalfExtents = first->boxExtents * 0.5f;
    glm::vec2 sHalfExtents = second->boxExtents * 0.5f;

    glm::vec2 fMax = fPos + fHalfExtents;
    glm::vec2 fMin = fPos - fHalfExtents;

    glm::vec2 sMax = sPos + sHalfExtents;
    glm::vec2 sMin = sPos - sHalfExtents;
    
    float fRotation = first->entity->transform->globalRotationDegrees;
    float sRotation = second->entity->transform->globalRotationDegrees;
        //Use AABB Collisions
    bool intersection = fPos.x > (sPos.x + second->boxExtents.x) || sPos.x > (fPos.x + first->boxExtents.x)
        || fPos.y > (sPos.y + second->boxExtents.y) || sPos.y > (fPos.y + first->boxExtents.y);
    
    
    if(!intersection)
    {
        const glm::vec2 faces[4] = 
        {
            glm::vec2(-1, 0), glm::vec2(1, 0),
            glm::vec2(0, -1), glm::vec2(0, 1)
        };

        float distances[4] = 
        {
            (sMax.x - fMin.x), //distance of second box to LEFT of first box
            (fMax.x - sMin.x), //distance of second box to RIGHT of first box
            (sMax.y - fMin.y), //distance of second box to BOTTOM of first box
            (fMax.y - sMin.y)  //distance of second box to TOP of first box
        };
        float penetration = FLT_MAX;
        glm::vec2 bestAxis;

        for(int i = 0; i < 4; i++)
        {
            if(distances[i] < penetration)
            {
                penetration = distances[i];
                bestAxis = faces[i];
            }
        }
        glm::vec2 a, b;

        collisionInfo.AddContactPoint(a, b, bestAxis, penetration);
        collisionInfo.first = first;
        collisionInfo.second = second;
        return true;
    }
    return !intersection;
}

bool Collision::CheckCollision(CircleCollision* first, BoxCollision* second, CollisionInfo& collisionInfo)
{
    glm::vec2 fPos = first->entity->transform->globalPosition + first->offset;
    glm::vec2 sPos = second->entity->transform->globalPosition + second->offset;
    glm::vec2 halfExtents = second->boxExtents * 0.5f;

    glm::vec2 delta = fPos - sPos;
    glm::vec2 closestPointOnBox = glm::clamp(delta, -halfExtents, halfExtents);

    glm::vec2 localPoint = delta - closestPointOnBox;
    float distance = glm::length(localPoint);

    if(distance < first->radius)
    {
        float penetration = distance - first->radius;
        glm::vec2 normal = glm::normalize(localPoint);
        glm::vec2 a;
        glm::vec2 b = -normal * first->radius;

        collisionInfo.AddContactPoint(a, b, normal, penetration);
        collisionInfo.first = first;
        collisionInfo.second = second;
        return true;
    }
    return false;
}

bool Collision::CheckCollision(CircleCollision* first, CircleCollision* second, CollisionInfo& collisionInfo)
{
    glm::vec2 fPos = first->entity->transform->globalPosition + first->offset;
    glm::vec2 sPos = second->entity->transform->globalPosition + second->offset;

    float radii = first->radius + second->radius;
    glm::vec2 delta = sPos - fPos;
    float deltaLength = glm::length(delta);

    if(deltaLength < radii)
    {
        float penetration = (radii - deltaLength);
        glm::vec2 normal = glm::normalize(delta);
        glm::vec2 a = normal * first->radius;
        glm::vec2 b = -normal * second->radius;

        collisionInfo.AddContactPoint(a, b, normal, penetration);
        collisionInfo.first = first;
        collisionInfo.second = second;
        return true;
    }
    return false;
}