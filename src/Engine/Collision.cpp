#include "Collision.h"
#include "BoxCollision.h"
#include "CircleCollision.h"

bool Collision::IsColliding(Collision* other)
{
    return IsColliding(this, other);
}

bool Collision::IsColliding(Collision* first, Collision* second)
{
    switch(first->shape)
    {
        case ShapeType::Box:
        switch(second->shape)
        {
            case ShapeType::Box:
                return Collision::IsColliding(dynamic_cast<BoxCollision*>(first), dynamic_cast<BoxCollision*>(second));
                break;
            case ShapeType::Circle:
                return Collision::IsColliding(dynamic_cast<CircleCollision*>(second), dynamic_cast<BoxCollision*>(first));
                break;
        }
        break;
        case ShapeType::Circle:
        switch(second->shape)
        {
            case ShapeType::Box:
                return Collision::IsColliding(dynamic_cast<CircleCollision*>(first), dynamic_cast<BoxCollision*>(second));
                break;
            case ShapeType::Circle:
                return Collision::IsColliding(dynamic_cast<CircleCollision*>(second), dynamic_cast<CircleCollision*>(first));
                break;
        }
        break;
    }
    return false;
}

bool Collision::IsColliding(BoxCollision* first, BoxCollision* second)
{
    Transform2D* fTrans = first->entity->transform;
    Transform2D* sTrans = second->entity->transform;

    bool intersection = fTrans->globalPosition.x > (sTrans->globalPosition.x + second->boxExtents.x) || sTrans->globalPosition.x > (fTrans->globalPosition.x + first->boxExtents.x)
        || fTrans->globalPosition.y > (sTrans->globalPosition.y + second->boxExtents.y) || sTrans->globalPosition.y > (fTrans->globalPosition.y + first->boxExtents.y);
    return !intersection;
}

bool Collision::IsColliding(CircleCollision* first, BoxCollision* second)
{
    glm::vec2 fPos = first->entity->transform->globalPosition + first->offset;
    glm::vec2 sPos = second->entity->transform->globalPosition + second->offset;
    glm::vec2 sScale = second->entity->transform->globalScale * second->boxExtents;

    glm::vec2 closestPoint;

    if(fPos.x < sPos.x)
        closestPoint.x = sPos.x;
    else if(fPos.x > sPos.x + sScale.x)
        closestPoint.x = sPos.x + sScale.x;
    else
        closestPoint.x = fPos.x;
    
    if(fPos.y < sPos.y)
        closestPoint.y = sPos.y;
    else if(fPos.y > sPos.y + sScale.y)
        closestPoint.y = sPos.y + sScale.y;
    else
        closestPoint.y = fPos.y;
    
    float xDelta = closestPoint.x - fPos.x;
    float yDelta = closestPoint.y - fPos.y;

    float distanceSquared = (xDelta * xDelta) + (yDelta * yDelta);

    return distanceSquared < (first->radius * first->radius);
}

bool Collision::IsColliding(CircleCollision* first, CircleCollision* second)
{
    glm::vec2 fPos = first->entity->transform->globalPosition + first->offset;
    glm::vec2 sPos = second->entity->transform->globalPosition + second->offset;

    float totalRadiusSquared = first->radius + second->radius;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    float xDelta = sPos.x - fPos.x;
    float yDelta = sPos.y - fPos.y;

    float distanceSquared = (xDelta * xDelta) + (yDelta * yDelta);
    
    return distanceSquared < totalRadiusSquared;
}