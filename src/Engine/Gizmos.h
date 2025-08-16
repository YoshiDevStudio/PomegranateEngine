#pragma once

#include "DLL_Build.h"
#include "Application.h"

struct Gizmo
{
    enum DrawType
    {
        Line,
        Rect,
        Circle
    } drawType;
    glm::vec2 firstArg;
    glm::vec2 secondArg;
    glm::vec4 color;

    Gizmo(DrawType drawType, glm::vec2 firstArg, glm::vec2 secondArg, glm::vec4 color)
    {
        this->drawType = drawType;
        this->firstArg = firstArg;
        this->secondArg = secondArg;
        this->color = color;
    }
};

class DLL_API Gizmos
{
public:
    static void DrawQueued();

    static void DrawLine(glm::vec2 start, glm::vec2 end, glm::vec4 color);
    static void DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color);
    static void DrawCircle(glm::vec2 position, int radius, glm::vec4 color);

private:
    static void CircleAlgorithm(glm::vec2 position, int radius);

    static std::vector<Gizmo> queuedGizmos;
};