#include "Tilemap.h"

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
    Tile tile = File::loadedTiles[texName][tileIndex];
    SetTile(globalPosition, tile);
}

void Tilemap::SetTile(glm::ivec2 globalPosition, Tile tile)
{
    globalPosition = AlignPosToGrid(globalPosition);
    std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
    auto it = tilemap.find(sPos);
    if(it != tilemap.end())
    {
        //sPos already exists, aka tile is already placed in this position
        tilemap.erase(it);
    }
    tile.position = globalPosition;
    tilemap.emplace(sPos, tile);
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

//!!FIXME: Alignment gets messed up when originalPos is negative
glm::ivec2 Tilemap::AlignPosToGrid(glm::ivec2 position)
{
    position -= (glm::ivec2)entity->transform->globalPosition;
    glm::ivec2 originalPos = position + (glm::ivec2)entity->transform->globalPosition;
    glm::ivec2 newPos = position;
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

    dstRect.x = position.x + (int)entity->transform->globalPosition.x;
    dstRect.y = position.y + (int)entity->transform->globalPosition.y;
    dstRect.w = tileSize * entity->transform->globalScale.x;
    dstRect.h = tileSize * entity->transform->globalScale.y;

    srcRect.x = tile.texturePosition.x;
    srcRect.y = tile.texturePosition.y;
    srcRect.w = tileSize;
    srcRect.h = tileSize;

    center.x = dstRect.w / 2.0;
    center.y = dstRect.h / 2.0;

    QueuedDraw* drawCall = new QueuedDraw(tile.tex2D->texture, &srcRect, &dstRect, tile.zIndex, entity->transform->globalRotationDegrees, &center);
    RenderManager::Queue(drawCall);
}

