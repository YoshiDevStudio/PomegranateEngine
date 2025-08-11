#pragma once

#include "Core.h"

struct DLL_API QueuedDraw
{
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect;
    SDL_FRect dstRect;
    int zIndex = 0;
    float rotation = 0;
    SDL_FPoint center;
    SDL_FlipMode flipMode = SDL_FLIP_NONE;

    QueuedDraw() = default;
    QueuedDraw(SDL_Texture* texture, SDL_FRect* srcRect, SDL_FRect* dstRect, int zIndex, float rotation, SDL_FPoint* center, SDL_FlipMode flipMode = SDL_FLIP_NONE)
    {
        //We have to reconstruct all pointers which would be freed after the original function they're created in, aka srcRect, dstRect, center
        this->texture = texture;
        SDL_FRect src = *srcRect;
        this->srcRect = src;

        SDL_FRect dst = *dstRect;
        this->dstRect = dst;

        this->zIndex = zIndex;
        this->rotation = rotation;
        SDL_FPoint p = *center;
        this->center = p;
        
        this->flipMode = flipMode;
    }
};

class DLL_API RenderManager
{
public:
    static void Queue(QueuedDraw* drawCall);
    static void Draw(SDL_Renderer* renderer);
private:
    //Sort queued draw calls by z order
    static void DescendingSort();
    static std::vector<QueuedDraw*> drawCalls;
};