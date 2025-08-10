#pragma once

#include "DLL_Build.h"
#include "SpriteRenderer.h"
#include "Event.h"

struct DLL_API AnimationFrame
{
public:
    Texture2D* tex2D;
    SDL_FRect clipRect;

    AnimationFrame()
    {
        this->tex2D = nullptr;
    }

    AnimationFrame(Texture2D* tex2D, Event<void>* event = nullptr)
    {
        this->tex2D = tex2D;
        SDL_FRect rect;

        rect.x = 0;
        rect.y = 0;
        rect.w = tex2D->width;
        rect.h = tex2D->height;

        this->clipRect = rect;
    }

    AnimationFrame(SDL_FRect clipRect, Event<void>* event = nullptr)
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

class DLL_API Animator : public Component
{
    
public:
    Animator(SpriteRenderer* sprite = nullptr);
    ~Animator() = default;

    virtual void OnAttach() override;
    virtual void Update() override;

    void PlayAnimation(Animation* animation);
    void SetPause(bool shouldPause);
    void StopAnimation();

    SpriteRenderer* sprite = nullptr;

    float animationSpeed = 1;
    bool isPlaying = false;
private:
    void UpdateFrame();
    bool SetSpriteRenderer(SpriteRenderer* sprite);
    
    Animation* currentAnimation = nullptr;
    AnimationFrame defaultState;

    Uint64 startOffset;
};