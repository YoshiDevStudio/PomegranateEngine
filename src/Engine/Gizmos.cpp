#include "Gizmos.h"

std::vector<Gizmo> Gizmos::queuedGizmos;

void Gizmos::DrawQueued()
{
    for(int i = 0; i < queuedGizmos.size(); i++)
    {
        SDL_FRect rect;
        rect.x = queuedGizmos[i].firstArg.x;
        rect.y = queuedGizmos[i].firstArg.y;
        rect.w = queuedGizmos[i].secondArg.x;
        rect.h = queuedGizmos[i].secondArg.y;

        glm::vec4 color = queuedGizmos[i].color;

        SDL_SetRenderDrawColorFloat(Application::window->renderer, color.r, color.g, color.b, color.a);
        switch(queuedGizmos[i].drawType)
        {
            case Gizmo::Line:
                SDL_RenderLine(Application::window->renderer, rect.x, rect.y, rect.w, rect.h);
                break;
            case Gizmo::Rect:
                SDL_RenderRect(Application::window->renderer, &rect);
                break;
            case Gizmo::Circle:
                CircleAlgorithm(queuedGizmos[i].firstArg, queuedGizmos[i].secondArg.x);
                break;
        }
    }
    queuedGizmos.clear();
}

void Gizmos::DrawLine(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
    Gizmo line(Gizmo::Line, start, end, color);
    queuedGizmos.push_back(line);
}

void Gizmos::DrawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color)
{
    Gizmo rect(Gizmo::Rect, position, size, color);
    queuedGizmos.push_back(rect);
}

void Gizmos::DrawCircle(glm::vec2 position, int radius, glm::vec4 color)
{
    Gizmo circle(Gizmo::Circle, position, glm::vec2(radius, radius), color);
    queuedGizmos.push_back(circle);
}

void Gizmos::CircleAlgorithm(glm::vec2 position, int radius)
{
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        SDL_FPoint point;
        point.x = position.x + x;
        point.y = position.y + y;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 + x, y0 + y);
        point.x = position.x + y;
        point.y = position.y + x;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 + y, y0 + x);
        point.x = position.x - y;
        point.y = position.y + x;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 - y, y0 + x);
        point.x = position.x - x;
        point.y = position.y + y;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 - x, y0 + y);
        point.x = position.x - x;
        point.y = position.y - y;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 - x, y0 - y);
        point.x = position.x - y;
        point.y = position.y - x;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 - y, y0 - x);
        point.x = position.x + y;
        point.y = position.y - x;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 + y, y0 - x);
        point.x = position.x + x;
        point.y = position.y - y;
        SDL_RenderPoint(Application::window->renderer, point.x, point.y);
        //putpixel(x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}