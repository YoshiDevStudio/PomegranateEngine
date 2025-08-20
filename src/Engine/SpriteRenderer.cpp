#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
    : Component()
{

}

SpriteRenderer::SpriteRenderer(Texture2D* tex2D)
    : Component()
{
    SetTexture(tex2D);
}

SpriteRenderer::SpriteRenderer(std::string texName)
    : Component()
{
    SetTexture(texName);
}

void SpriteRenderer::Update()
{
    Component::Update();
    this->Draw();
}

void SpriteRenderer::Draw()
{
    if(entity == nullptr || tex2D == nullptr || tex2D->texture == nullptr)
        return;

    SDL_FRect dstRect;
    SDL_FRect srcRect;
    SDL_FPoint center;

    //center texture
    dstRect.x = entity->transform->globalPosition.x - (tex2D->size.x * 0.5f * entity->transform->globalScale.x);
    dstRect.y = entity->transform->globalPosition.y - (tex2D->size.y * 0.5f * entity->transform->globalScale.y);
    dstRect.w = ((float)tex2D->size.x) * entity->transform->globalScale.x;
    dstRect.h = ((float)tex2D->size.y) * entity->transform->globalScale.y;

    srcRect.x = clipRect.x;
    srcRect.y = clipRect.y;
    srcRect.w = clipRect.w;
    srcRect.h = clipRect.h;

    center.x = dstRect.w / 2.0;
    center.y = dstRect.h / 2.0;

    QueuedDraw* drawCall = new QueuedDraw(tex2D->texture, &srcRect, &dstRect, zIndex, entity->transform->globalRotationDegrees, &center, flipMode);
    RenderManager::Queue(drawCall);
}

void SpriteRenderer::SetTexture(Texture2D* tex2D)
{
    if(tex2D == nullptr)
    {
        LOG_ERROR("Texture assigned to SpriteRenderer was null");
        return;
    }
    this->tex2D = tex2D;
    ResetClipRect();
}

void SpriteRenderer::SetTexture(std::string texName)
{
    SetTexture(File::loadedTextures[texName]);
}

Texture2D* SpriteRenderer::GetTexture()
{
    return this->tex2D;
}

void SpriteRenderer::ResetClipRect()
{
    SDL_FRect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = GetTexture()->size.x;
    rect.h = GetTexture()->size.y;

    clipRect = rect;
}