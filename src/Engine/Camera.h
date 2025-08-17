#pragma once

#include "Core.h"
#include "Transform2D.h"

class Application;

class DLL_API Camera : public Component
{
public:
    static Camera* currentCamera;

    Camera(bool isCurrent = false);
    ~Camera() = default;

    void SetCurrent(bool current);
    void SetSize(glm::vec2 size);
    glm::vec2 GetSize();
    glm::vec2 GetCenterPos();

private:
    glm::vec2 size = glm::vec2(1920, 1080);
    bool isCurrent = false;
};