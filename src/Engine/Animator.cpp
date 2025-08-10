#include "Animator.h"


Animator::Animator(SpriteRenderer* sprite)
    : Component()
{
    SetSpriteRenderer(sprite);
}

void Animator::OnAttach()
{
    SetSpriteRenderer(entity->GetComponent<SpriteRenderer>());
}

void Animator::Update()
{
    Component::Update();
    this->UpdateFrame();
}

void Animator::PlayAnimation(Animation* animation)
{
    if(sprite == nullptr && entity != nullptr)
    {
        if(!SetSpriteRenderer(entity->GetComponent<SpriteRenderer>()))
        {
            LOG_ERROR("SpriteRenderer not found on Entity: " + entity->GetName());
        }
        return;
    }
    currentAnimation = animation;
    isPlaying = true;
}

void Animator::Pause()
{
    isPlaying = false;
}

void Animator::StopAnimation()
{
    Animation defaultAnim;
    defaultAnim.AddFrame(&defaultState);
    currentAnimation = &defaultAnim;
}

//returns if SpriteRenderer was found
bool Animator::SetSpriteRenderer(SpriteRenderer* sprite)
{
    if(sprite != nullptr)
    {
        this->sprite = sprite;
        defaultState.clipRect = sprite->clipRect;
        defaultState.tex2D = sprite->GetTexture();
        return true;
    }
    return false;
}

void Animator::UpdateFrame()
{
    if(currentAnimation == nullptr || !isPlaying || sprite == nullptr)
        return;
    //LOG("before");
    
    //LOG("after")
    currentAnimationTimer = (SDL_GetTicks() / 1000.0f) * animationSpeed;
    int index = currentAnimationTimer % currentAnimation->frames.size();
    AnimationFrame frame = currentAnimation->frames[index];
    sprite->clipRect = frame.clipRect;
    if(frame.tex2D == nullptr)
        return;
        
    sprite->SetTexture(frame.tex2D);
}