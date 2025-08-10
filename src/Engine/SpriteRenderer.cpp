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

    SDL_FRect dstRect;
    SDL_FRect srcRect;
    SDL_FPoint center;

    dstRect.x = entity->transform->globalPosition.x;
    dstRect.y = entity->transform->globalPosition.y;
    dstRect.w = ((float)tex2D->width) * entity->transform->globalScale.x;
    dstRect.h = ((float)tex2D->height) * entity->transform->globalScale.y;

    srcRect.x = dstRect.x;
    srcRect.y = dstRect.y;
    srcRect.w = clipRect.x * entity->transform->globalScale.x;
    srcRect.h = clipRect.y * entity->transform->globalScale.y;

    center.x = dstRect.w / 2.0;
    center.y = dstRect.h / 2.0;

    SDL_RenderTextureRotated(window->renderer, tex2D->texture, &srcRect, &dstRect, entity->transform->globalRotationDegrees, &center, SDL_FLIP_NONE);
}

void SpriteRenderer::SetTexture(Texture2D* tex2D)
{
    if(tex2D == nullptr)
    {
        LOG_ERROR("Texture assigned was null");
        return;
    }
    this->tex2D = tex2D;
    if(clipRect == glm::vec2(0, 0))
    {
        clipRect = glm::vec2(tex2D->width, tex2D->height);
    }
}

void SpriteRenderer::SetTexture(std::string texName)
{
    SetTexture(File::loadedTextures[texName]);
}

Texture2D* SpriteRenderer::GetTexture()
{
    return this->tex2D;
}