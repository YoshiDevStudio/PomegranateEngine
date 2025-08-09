#pragma once

#include <SDL3/SDL.h>

#include "DLL_Build.h"

class DLL_API Texture2D
{
public:
    Texture2D(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
    ~Texture2D()
    {
        delete texture;
    }
    
    int width, height;
    SDL_Texture* texture = nullptr;
};