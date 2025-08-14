#pragma once

#include <SDL3/SDL.h>

#include "DLL_Build.h"

class DLL_API Texture2D
{
public:
    Texture2D(int width, int height)
    {
        this->size.x = width;
        this->size.y = height;
    }
    ~Texture2D()
    {
        delete texture;
    }
    
    glm::vec2 size;
    SDL_Texture* texture = nullptr;
};