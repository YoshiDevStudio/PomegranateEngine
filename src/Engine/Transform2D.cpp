#include "Transform2D.h"

Transform2D::Transform2D()
    : Component()
{

}

void Transform2D::Update()
{
    Component::Update();
    ApplyTransformations();
}

void Transform2D::ApplyTransformations()
{
    if(entity == nullptr)
        return;

    glm::vec2 parentPos = glm::vec2(0, 0);
    float parentRotationDegrees = 0;
    glm::vec2 parentScale = glm::vec2(1, 1);

    Entity* parent = entity->GetParent();
    if(parent != nullptr)
    {
        parentPos = parent->transform->globalPosition;
        parentRotationDegrees = parent->transform->globalRotationDegrees;
        parentScale = parent->transform->globalScale;
    }

    globalPosition = localPosition + parentPos;
    globalRotationDegrees = localRotationDegrees + parentRotationDegrees;
    globalScale = localScale * parentScale;
}