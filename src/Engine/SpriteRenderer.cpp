#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Window* window)
    : Component()
{
    this->window = window;
}

SpriteRenderer::SpriteRenderer(Window* window, Texture2D* tex2D)
    : Component()
{
    SetTexture(tex2D);
    this->window = window;
}

SpriteRenderer::SpriteRenderer(Window* window, std::string texName)
    : Component()
{
    SetTexture(texName);
    this->window = window;
}

void SpriteRenderer::Update()
{
    Component::Update();
    this->Draw();
}

void SpriteRenderer::Draw()
{
    if(entity == nullptr || tex2D == nullptr)
        return;

    SDL_FPoint center;
    SDL_FRect dstRect;
    glm::ivec2 windowRect = window->GetWindowRect();

    dstRect.x = (((float)(windowRect.x - tex2D->width)) / 2.0f) + entity->transform->globalPosition.x;
    dstRect.y = (((float)(windowRect.y - tex2D->height)) / 2.0f) + entity->transform->globalPosition.y;
    dstRect.w = ((float)tex2D->width) * entity->transform->globalScale.x;
    dstRect.h = ((float)tex2D->height) * entity->transform->globalScale.y;

    center.x = dstRect.w / 2.0;
    center.y = dstRect.h / 2.0;

    SDL_RenderTextureRotated(window->renderer, tex2D->texture, NULL, &dstRect, entity->transform->globalRotationDegrees, &center, SDL_FLIP_NONE);
}

void SpriteRenderer::SetTexture(Texture2D* tex2D)
{
    if(tex2D == nullptr)
        LOG_WARNING("Texture assigned was null");
    this->tex2D = tex2D;
}

void SpriteRenderer::SetTexture(std::string texName)
{
    SetTexture(File::loadedTextures[texName]);
}

Texture2D* SpriteRenderer::GetTexture()
{
    return this->tex2D;
}