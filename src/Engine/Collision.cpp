#include "Collision.h"
#include "BoxCollision.h"
#include "CircleCollision.h"
#include "PhysicsBody.h"
#include "Ray.h"

void Collision::OnAttach()
{
    GetPhysicsBody();
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

bool Collision::CheckRayCollision(const Ray& ray, RaycastHit& hitInfo)
{
    if((1 << ray.GetMask() &  1 << this->GetCollisionLayer()))
    {
        switch(this->shape)
        {
            case ShapeType::Box:
                return RayCollision(ray, dynamic_cast<BoxCollision*>(this), hitInfo);
                break;
            case ShapeType::Circle:
                return RayCollision(ray, dynamic_cast<CircleCollision*>(this), hitInfo);
                break;
        }
    }
    return false;
}

glm::vec2 Collision::GetGlobalPosition()
{
    if(this->entity == nullptr)
    {
        return this->offset;
    }
    return this->entity->transform->globalPosition + offset;
}

PhysicsBody* Collision::GetPhysicsBody()
{
    if(body == nullptr)
        body = entity->GetComponent<PhysicsBody>();
    return body;
}

void Collision::SetCollisionLayer(unsigned int collisionLayer)
{
    this->collisionLayer = collisionLayer;
}

unsigned int Collision::GetCollisionLayer()
{
    return collisionLayer;
}

void Collision::SetCollisionMask(unsigned int collisionMask)
{
    this->collisionMask = collisionMask;
}

unsigned int Collision::GetCollisionMask()
{
    return collisionMask;
}

bool Collision::AABBTest(glm::vec2 fPos, glm::vec2 sPos, glm::vec2 fSize, glm::vec2 sSize)
{
    bool intersection = (fPos.x - fSize.x) > (sPos.x + sSize.x) || (sPos.x - sSize.x) > (fPos.x + fSize.x)
        || (fPos.y - fSize.y) > (sPos.y + sSize.y) || (sPos.y - sSize.y) > (fPos.y + fSize.y);
    
    return !intersection;
}

bool Collision::CheckCollision(Collision* first, Collision* second, CollisionInfo& collisionInfo)
{
    if((1 << first->GetCollisionLayer() &  1 << second->GetCollisionMask()))
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
    }
    return false;
}

bool Collision::CheckCollision(BoxCollision* first, BoxCollision* second, CollisionInfo& collisionInfo)
{
    glm::vec2 fPos;
    glm::vec2 sPos;
    if(first->entity != nullptr)
        fPos = first->entity->transform->globalPosition + first->offset;
    else
        fPos = first->offset;
    if(second->entity != nullptr)
        sPos = second->entity->transform->globalPosition + second->offset;
    else
        sPos = second->offset;

    glm::vec2 fHalfExtents = first->boxExtents * 0.5f;
    glm::vec2 sHalfExtents = second->boxExtents * 0.5f;

    glm::vec2 fMax = fPos + fHalfExtents;
    glm::vec2 fMin = fPos - fHalfExtents;

    glm::vec2 sMax = sPos + sHalfExtents;
    glm::vec2 sMin = sPos - sHalfExtents;
    
        //Use AABB Collisions
    bool isColliding = AABBTest(fPos, sPos, fHalfExtents, sHalfExtents);
    
    
    if(isColliding)
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
    return false;
}

bool Collision::CheckCollision(CircleCollision* first, BoxCollision* second, CollisionInfo& collisionInfo)
{
    glm::vec2 fPos;
    glm::vec2 sPos;
    if(first->entity != nullptr)
        fPos = first->entity->transform->globalPosition + first->offset;
    else
        fPos = first->offset;
    if(second->entity != nullptr)
        sPos = second->entity->transform->globalPosition + second->offset;
    else
        sPos = second->offset;

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
    glm::vec2 fPos;
    glm::vec2 sPos;
    if(first->entity != nullptr)
        fPos = first->entity->transform->globalPosition + first->offset;
    else
        fPos = first->offset;
    if(second->entity != nullptr)
        sPos = second->entity->transform->globalPosition + second->offset;
    else
        sPos = second->offset;

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

bool Collision::RayCollision(const Ray& ray, CircleCollision* collision, RaycastHit& hitInfo)
{
    glm::vec2 cPos;
    if(collision->entity != nullptr)
        cPos = collision->entity->transform->globalPosition + collision->offset;
    else
        cPos = collision->offset;
    
    //E
    glm::vec2 dir = (cPos - ray.GetPosition());
    //a
    float cProj = glm::dot(dir, ray.GetDirection());

    float rayDifference = glm::distance(cPos, ray.GetPosition());
    //if rayPos is outside of circle
    if(rayDifference > collision->radius)
    {
        if(cProj < 0.0f)
            return false;
    }
    
    glm::vec2 point = ray.GetPosition() + (ray.GetDirection() * cProj);
    //b
    float cDst = glm::length((cPos - point));

    if(cDst > collision->radius)
    {
        return false;
    }

    //f
    float offset = sqrt((collision->radius * collision->radius) - (cDst * cDst));

    float rayDst;
    //if rayPos is outside of circle
    if(rayDifference > collision->radius)
        rayDst = (cProj - offset);
    else
        rayDst = (cProj + offset);
    if(rayDst < hitInfo.rayDistance)
    {
        hitInfo.rayDistance = rayDst;
        hitInfo.hitPosition = ray.GetPosition() + (ray.GetDirection() * hitInfo.rayDistance);
        hitInfo.object = collision;
        hitInfo.hit = true;
        return true;
    }
    return false;
}

bool Collision::RayCollision(const Ray& ray, BoxCollision* collision, RaycastHit& hitInfo)
{
    glm::vec2 cPos;
    if(collision->entity != nullptr)
        cPos = collision->entity->transform->globalPosition + collision->offset;
    else
        cPos = collision->offset;

    glm::vec2 halfExtents = collision->boxExtents * 0.5f;

    glm::vec2 boxMin = cPos - halfExtents;
    glm::vec2 boxMax = cPos + halfExtents;

    glm::vec2 rayPos = ray.GetPosition();
    glm::vec2 rayInverseDir = 1.0f / ray.GetDirection();

    glm::vec2 tVals1 = glm::vec2((boxMin.x - rayPos.x) * rayInverseDir.x, (boxMin.y - rayPos.y) * rayInverseDir.y);
    glm::vec2 tVals2 = glm::vec2((boxMax.x - rayPos.x) * rayInverseDir.x, (boxMax.y - rayPos.y) * rayInverseDir.y);

    float tMin = std::max(std::min(tVals1.x, tVals2.x), std::min(tVals1.y, tVals2.y));
    float tMax = std::min(std::max(tVals1.x, tVals2.x), std::max(tVals1.y, tVals2.y));

    if(tMax >= tMin)
    {
        //Decide if box is getting hit from outside or inside
        float bestTOuter = std::min(tMin, tMax);
        float bestTInner = std::max(tMin, tMax);
        float bestT = bestTOuter;
        if(bestTOuter < 0.0f)
        {
            if(bestTInner < 0.0f)
                return false;
            bestT = bestTInner;
        }
        glm::vec2 intersection = rayPos + (ray.GetDirection() * bestT);

        if(bestT < hitInfo.rayDistance)
        {
            hitInfo.hitPosition = intersection;
            hitInfo.rayDistance = bestT;
            hitInfo.object = collision;
            hitInfo.hit = true;
            return true;
        }
    }

    return false;
}
