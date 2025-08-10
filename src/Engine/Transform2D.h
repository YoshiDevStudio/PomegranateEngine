#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <cmath>

class Transform2D : public Component
{
public:
    Transform2D();
    ~Transform2D() = default;

    virtual void Update() override;

    glm::vec2 globalPosition = glm::vec2(0, 0);
    glm::vec2 localPosition = glm::vec2(0, 0);

    float globalRotationDegrees = 0;
    float localRotationDegrees = 0;

    glm::vec2 globalScale = glm::vec2(1, 1);
    glm::vec2 localScale = glm::vec2(1, 1);
private:
    void ApplyTransformations();
};