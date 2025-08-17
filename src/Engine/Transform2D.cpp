#include "Transform2D.h"
#include "Application.h"
#include "Camera.h"

Transform2D::Transform2D()
    : Component()
{

}

void Transform2D::Update()
{
    Component::Update();
    ApplyTransformations();
}

glm::vec2 Transform2D::WorldToScreen(glm::vec2 worldPos)
{
    Camera* cam = Camera::currentCamera;
    if(cam != nullptr)
    {
        glm::vec2 camSize = cam->GetSize();
        glm::vec2 windowSize = Application::window->GetWindowSize();
        
        worldPos /= (camSize / windowSize);
        return worldPos + cam->GetCenterPos();
    }
    return worldPos;
}

glm::vec2 Transform2D::ScreenToWorld(glm::vec2 screenPos)
{
    Camera* cam = Camera::currentCamera;
    if(cam != nullptr)
    {
        glm::vec2 camSize = cam->GetSize();
        glm::vec2 windowSize = Application::window->GetWindowSize();
        
        screenPos *= (camSize / windowSize);
        return screenPos + cam->GetCenterPos();
    }
    return screenPos;
}

//recursively gets all parents added positions
glm::vec2 Transform2D::GetParentPosition()
{
    if(entity->GetParent() != nullptr)
    {
        if(entity->GetParent()->GetParent() != nullptr)
            return entity->GetParent()->transform->localPosition += entity->GetParent()->GetParent()->transform->GetParentPosition();
        
        return entity->GetParent()->transform->localPosition;
    }
    return glm::vec2(0, 0);
}

float Transform2D::GetParentRotation()
{
    if(entity->GetParent() != nullptr)
    {
        if(entity->GetParent()->GetParent() != nullptr)
            return entity->GetParent()->transform->localRotationDegrees += entity->GetParent()->GetParent()->transform->GetParentRotation();
        
        return entity->GetParent()->transform->localRotationDegrees;
    }
    return 0.0f;
}

glm::vec2 Transform2D::GetParentScale()
{
    if(entity->GetParent() != nullptr)
    {
        if(entity->GetParent()->GetParent() != nullptr)
            return entity->GetParent()->transform->localScale += entity->GetParent()->GetParent()->transform->GetParentScale();
        
        return entity->GetParent()->transform->localScale;
    }
    return glm::vec2(0, 0);
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
        parentPos = GetParentPosition();
        parentRotationDegrees = GetParentRotation();
        parentScale = GetParentScale();
    }

    globalPosition = localPosition + parentPos;
    globalRotationDegrees = localRotationDegrees + parentRotationDegrees;
    globalScale = localScale * parentScale;
}