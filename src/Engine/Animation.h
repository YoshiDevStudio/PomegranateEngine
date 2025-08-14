#pragma once

#include <vector>
#include "DLL_Build.h"
#include "Texture2D.h"

struct DLL_API AnimationFrame
{
public:
    Texture2D* tex2D;
    SDL_FRect clipRect;

    AnimationFrame()
    {
        this->tex2D = nullptr;
    }

    AnimationFrame(Texture2D* tex2D)
    {
        this->tex2D = tex2D;
        SDL_FRect rect;

        rect.x = 0;
        rect.y = 0;
        rect.w = tex2D->size.x;
        rect.h = tex2D->size.y;

        this->clipRect = rect;
    }

    AnimationFrame(SDL_FRect clipRect)
    {
        this->tex2D = nullptr;
        this->clipRect = clipRect;
    }
};

class DLL_API Animation
{
public:
    Animation()
    {
        
    }
    ~Animation() = default;

    void AddFrame(SDL_FRect clipRect)
    {
        AnimationFrame frame(clipRect);
        frames.push_back(frame);
    }

    void AddFrame(Texture2D* tex2D)
    {
        AnimationFrame frame(tex2D);
        frames.push_back(frame);
    }

    void AddFrame(AnimationFrame* frame)
    {
        frames.push_back(*frame);
    }

    void RemoveFrameAt(int index)
    {
        frames.erase(frames.begin() + index);
    }
    std::vector<AnimationFrame> frames;
};