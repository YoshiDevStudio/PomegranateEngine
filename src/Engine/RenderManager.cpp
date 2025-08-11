#include "RenderManager.h"

std::vector<QueuedDraw*> RenderManager::drawCalls;

void RenderManager::Queue(QueuedDraw* drawCall)
{
    drawCalls.push_back(drawCall);
}

void RenderManager::Draw(SDL_Renderer* renderer)
{
    DescendingSort();
    for(int i = 0; i < drawCalls.size(); i++)
    {
        QueuedDraw* draw = drawCalls[i];
        if(draw == nullptr)
        {
            LOG_ERROR("Queued Draw call was nullptr");
            continue;
        }
        SDL_RenderTextureRotated(renderer, draw->texture, &draw->srcRect, &draw->dstRect, draw->rotation, &draw->center, draw->flipMode);
    }
    for(int i = 0; i < drawCalls.size(); i++)
    {
        delete drawCalls[i];
    }
    drawCalls.clear();
}

void RenderManager::DescendingSort()
{
    QueuedDraw* temp;
    for(int i = 0; i < drawCalls.size() - 1; i++)
    {
        for(int j = 0; j < drawCalls.size() - i - 1; j++)
        {
            if(drawCalls[j]->zIndex > drawCalls[j + 1]->zIndex)
            {
                temp = drawCalls[j];
                drawCalls[j] = drawCalls[j + 1];
                drawCalls[j + 1] = temp;
            }
        }
    }
}