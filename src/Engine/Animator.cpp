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
    timer = 0;
    isPlaying = true;
}

void Animator::Seek(float seconds)
{
    timer = seconds;
}

void Animator::SetPause(bool shouldPause)
{
    isPlaying = !shouldPause;
}

void Animator::StopAnimation()
{
    isPlaying = false;
    currentAnimation = nullptr;
    sprite->clipRect = defaultState.clipRect;
    sprite->SetTexture(defaultState.tex2D);
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
    
    timer += Time::deltaTime * animationSpeed;
    std::cout << "Timer: " << timer << std::endl;
    int index = (int)timer % currentAnimation->frames.size();
    AnimationFrame frame = currentAnimation->frames[index];

    sprite->clipRect = frame.clipRect;
    if(frame.tex2D == nullptr)
        return;

    sprite->SetTexture(frame.tex2D);
}