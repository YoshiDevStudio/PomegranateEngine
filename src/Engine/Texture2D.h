#pragma once

#include <SDL3/SDL.h>

class Texture2D
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