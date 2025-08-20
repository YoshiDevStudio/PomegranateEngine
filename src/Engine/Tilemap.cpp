#include "Tilemap.h"
#include "SpriteRenderer.h"
#include "BoxCollision.h"
#include "StaticBody.h"

Tilemap::Tilemap(int tileSize)
{
    this->tileSize = tileSize;
}

Tilemap::~Tilemap()
{
    
}

void Tilemap::Update()
{
    Component::Update();
    DrawTilemap();
}

void Tilemap::SetTile(glm::ivec2 globalPosition, std::string texName, int tileIndex)
{
    Tile* tile = File::loadedTiles[texName][tileIndex];
    SetTile(globalPosition, tile);
}

void Tilemap::SetTile(glm::ivec2 globalPosition, std::string texName, glm::ivec2 tileIndexPosition)
{
    Tile* tile = File::GetTileAtPos(texName, tileIndexPosition);
    SetTile(globalPosition, tile);
}

void Tilemap::SetTile(glm::ivec2 globalPosition, Tile* tile)
{

    glm::ivec2 originalPosition = globalPosition;
    globalPosition = AlignPosToGrid(globalPosition);
    std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
    
    EraseTile(originalPosition);
    EraseLogicTile(globalPosition);

    if(tile->hasCollision)
    {
        CreateLogicTile(originalPosition, tile);
        return;
    }
    
    Tile newTile(tile->texturePosition, tile->tex2D, tile->tileSize, tile->zIndex, tile->isReplaceable);
    newTile.position = globalPosition;
    tilemap.emplace(sPos, newTile);
    
}

Tile* Tilemap::GetTileAt(glm::ivec2 globalPosition)
{
    try
    {
        globalPosition = AlignPosToGrid(globalPosition);
        std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
        return &tilemap.at(sPos);
    }
    catch(std::out_of_range e)
    {
        return nullptr;
    }
}

Entity* Tilemap::GetTileEntityAt(glm::ivec2 globalPosition)
{
    try
    {
        globalPosition = AlignPosToGrid(globalPosition);
        std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
        return logicTilemap.at(sPos);
    }
    catch(std::out_of_range e)
    {
        return nullptr;
    }
}

void Tilemap::EraseTile(glm::ivec2 globalPosition)
{
    globalPosition = AlignPosToGrid(globalPosition);
    std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
    auto it = tilemap.find(sPos);
    if(it != tilemap.end())
    {
        //sPos already exists, aka tile is already placed in this position
        tilemap.erase(it);
    }
}

glm::ivec2 Tilemap::AlignPosToGrid(glm::ivec2 position)
{
    position -= (glm::ivec2)entity->transform->globalPosition;
    glm::ivec2 originalPos = position + (glm::ivec2)entity->transform->globalPosition;
    glm::ivec2 newPos = position;
    if(((newPos.x % tileSize) == 0) && ((newPos.y % tileSize) == 0))
        return newPos;

    if(position.x > 0)
    {
        if(tileSize / abs(position.x) < tileSize / 2)
        {
            //place on right side
            newPos.x +=  -((position.x) % tileSize);
        }
        else
        {
            //place on left side
            newPos.x -= ((position.x) % tileSize) + tileSize;
        }
    }
    else if(position.x < 0)
    {
        if(tileSize / abs(position.x) < tileSize / 2)
        {
            //place on left side
            newPos.x -= ((position.x) % tileSize) + tileSize;
        }
        else
        {
            //place on right side
            newPos.x +=  -((position.x) % tileSize);
        }
    }
    if(position.y > 0)
    {
        if(tileSize / abs(position.y) < tileSize / 2)
        {
            //place on right side
            newPos.y +=  -((position.y) % tileSize);
        }
        else
        {
            //place on left side
            newPos.y -= ((position.y) % tileSize) + tileSize;
        }
    }
    else if(position.y < 0)
    {
        if(tileSize / abs(position.y) < tileSize / 2)
        {
            //place on left side
            newPos.y -= ((position.y) % tileSize) + tileSize;
            
        }
        else
        {
            //place on right side
            newPos.y +=  -((position.y) % tileSize);
        }
    }
    return newPos;
}

Entity* Tilemap::CreateLogicTile(glm::ivec2 globalPosition, Tile* tile)
{
    EraseTile(globalPosition);

    globalPosition = AlignPosToGrid(globalPosition);
    std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
    //make tile with logic
    Entity* tileEntity = new Entity(sPos);
    tileEntity->transform->localPosition = globalPosition;
    tileEntity->transform->localScale = glm::vec2(0.5f, 1.0f);
    tileEntity->transform->localPosition += (tileSize * 0.5f * entity->transform->globalScale);

    SpriteRenderer* tileSprite = new SpriteRenderer(tile->tex2D);

    SDL_FRect tileRect;
    tileRect.x = tile->texturePosition.x;
    tileRect.y = tile->texturePosition.y;
    tileRect.w = tileSize;
    tileRect.h = tileSize;
    tileSprite->clipRect = tileRect;

    tileEntity->AddComponent(tileSprite);

    if(tile->hasCollision)
    {
        BoxCollision* collision = new BoxCollision(tile->tex2D->size * entity->transform->globalScale);
        collision->boxExtents.x *= 0.5f;
        collision->SetCollisionLayer(collisionLayer);
        collision->SetCollisionMask(collisionMask);
        StaticBody* body = new StaticBody();

        tileEntity->AddComponent(collision);
        tileEntity->AddComponent(body);
    }

    this->entity->AddChild(tileEntity);
    logicTilemap.emplace(sPos, tileEntity);
    return tileEntity;
}

void Tilemap::EraseLogicTile(glm::ivec2 globalPosition)
{
    std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
    auto it = logicTilemap.find(sPos);
    if(it != logicTilemap.end())
    {
        //sPos already exists, aka tile is already placed in this position
        logicTilemap.erase(it);
        Entity* child = this->entity->GetChild(sPos);
        if(child != nullptr)
        {
            delete child;
        }
    }
}

void Tilemap::DrawTilemap()
{
    if(entity == nullptr)
        return;
    for(const auto& pair : tilemap)
    {
        Tile tile = pair.second;
        DrawTile(tile.position, tile);
    }
}

void Tilemap::DrawTile(glm::vec2 position, Tile tile)
{
    //pos is relative to globalPosition
    if(tile.tex2D == nullptr || tile.texturePosition.x == -1 || tile.texturePosition.y == -1)
        return;
    Tile* currentTile = GetTileAt(position);
    if(currentTile != nullptr && !currentTile->isReplaceable)
    {
        return;
    }
    SDL_FRect dstRect;
    SDL_FRect srcRect;
    SDL_FPoint center;

    dstRect.x = position.x + entity->transform->globalPosition.x;
    dstRect.y = position.y + entity->transform->globalPosition.y;
    dstRect.w = tileSize * entity->transform->globalScale.x;
    dstRect.h = tileSize * entity->transform->globalScale.y;

    srcRect.x = tile.texturePosition.x;
    srcRect.y = tile.texturePosition.y;
    srcRect.w = tileSize;
    srcRect.h = tileSize;

    center.x = dstRect.w * 0.5f;
    center.y = dstRect.h * 0.5f;
    QueuedDraw* drawCall = new QueuedDraw(tile.tex2D->texture, &srcRect, &dstRect, tile.zIndex, entity->transform->globalRotationDegrees, &center);
    RenderManager::Queue(drawCall);
}

