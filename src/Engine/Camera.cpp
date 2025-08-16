#include "Camera.h"
#include "Application.h"

Camera* Camera::currentCamera = nullptr;

Camera::Camera(bool isCurrent)
{
    size = Application::window->GetWindowSize();
    SetCurrent(isCurrent);
}

void Camera::SetCurrent(bool current)
{
    if(current == true)
    {
        std::vector<Camera*> cameras = Application::GetAllComponentsOfType<Camera>();
        for(int i = 0; i < cameras.size(); i++)
        {
            cameras[i]->isCurrent = false;
        }
        this->isCurrent = true;
        currentCamera = this;
        return;
    }
    this->isCurrent = false;
}

glm::vec2 Camera::GetCenterPos()
{
    if(entity == nullptr)
        return glm::vec2(0, 0);
    return entity->transform->globalPosition - (size * 0.5f);
}