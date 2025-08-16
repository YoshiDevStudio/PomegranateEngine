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
    glm::vec2 GetCenterPos();

    glm::vec2 size;
private:
    bool isCurrent = false;
};