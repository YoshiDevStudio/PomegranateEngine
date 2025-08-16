#pragma once

#include "Core.h"
#include "SpriteRenderer.h"
#include "Event.h"
#include "Animation.h"

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