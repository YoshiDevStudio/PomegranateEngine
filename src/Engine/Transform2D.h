#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <cmath>

class DLL_API Transform2D : public Component
{
public:
    Transform2D();
    ~Transform2D() = default;

    virtual void Update() override;

    static glm::vec2 WorldToScreen(glm::vec2 worldPos);
    static glm::vec2 ScreenToWorld(glm::vec2 screenPos);

    glm::vec2 globalPosition = glm::vec2(0, 0);
    glm::vec2 localPosition = glm::vec2(0, 0);

    float globalRotationDegrees = 0;
    float localRotationDegrees = 0;

    glm::vec2 globalScale = glm::vec2(1, 1);
    glm::vec2 localScale = glm::vec2(1, 1);
private:
    glm::vec2 GetParentPosition();
    float GetParentRotation();
    glm::vec2 GetParentScale();

    void ApplyTransformations();

    
};