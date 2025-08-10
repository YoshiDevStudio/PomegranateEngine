#pragma once

#include "DLL_Build.h"
#include "SpriteRenderer.h"
#include "Event.h"

struct DLL_API AnimationFrame
{
public:
    Texture2D* tex2D;
    glm::vec2 clipRect;

    AnimationFrame()
    {
        this->tex2D = nullptr;
    }

    AnimationFrame(Texture2D* tex2D, Event<void>* event = nullptr)
    {
        this->tex2D = tex2D;
        this->clipRect = glm::vec2(tex2D->width, tex2D->height);
    }

    AnimationFrame(glm::vec2 clipRect, Event<void>* event = nullptr)
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

    void AddFrame(glm::vec2 clipRectFrame)
    {
        AnimationFrame frame(clipRectFrame);
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
    void Pause();
    void StopAnimation();

    SpriteRenderer* sprite = nullptr;

    float animationSpeed = 1;
    bool isPlaying = false;
private:
    void UpdateFrame();
    bool SetSpriteRenderer(SpriteRenderer* sprite);
    
    Animation* currentAnimation = nullptr;
    AnimationFrame defaultState;

    Uint64 currentAnimationTimer;
};