#pragma once

#include <unordered_map>
#include <vector>
#include "Transform2D.h"
#include "Tile.h"
#include "File.h"
#include "RenderManager.h"

class DLL_API Tilemap : public Component
{
public:
    Tilemap(int tileSize);
    ~Tilemap();
    virtual void Update() override;

    void SetTile(glm::ivec2 globalPosition, std::string texName, int tileIndex);
    void SetTile(glm::ivec2 globalPosition, std::string texName, glm::ivec2 tileIndexPosition);
    void SetTile(glm::ivec2 globalPosition, Tile* tile);
    //returns tile found at position. if tile has components attached to it, use GetTileEntityAt()
    Tile* GetTileAt(glm::ivec2 globalPosition);
    //return Entity found at position, if tile has no components attached to it, use GetTileAt()
    Entity* GetTileEntityAt(glm::ivec2 globalPosition);

    template <typename T>
    void AddComponentToTile(glm::ivec2 globalPosition, T* component)
    {
        if(component == nullptr)
            return;

        glm::ivec2 originalPos = globalPosition;
        globalPosition = AlignPosToGrid(globalPosition);
        std::string sPos = std::to_string(globalPosition.x) + "," + std::to_string(globalPosition.y);
        Tile* tile = GetTileAt(originalPos);

        auto it = logicTilemap.find(sPos);
        if(it != logicTilemap.end())
        {
            //sPos found
            Entity* tileEntity = it->second;
            tileEntity->AddComponent(component);
        }
        else
        {
            if(tile == nullptr)
                return;
            Entity* tileEntity = CreateLogicTile(originalPos, tile);
            tileEntity->AddComponent(component);
        }
    }

    void EraseTile(glm::ivec2 globalPosition);

    glm::ivec2 AlignPosToGrid(glm::ivec2 position);

    int tileSize;
    unsigned int collisionLayer = 0u;
    unsigned int collisionMask = 0u;
private:
    Entity* CreateLogicTile(glm::ivec2 globalPosition, Tile* tile);
    void EraseLogicTile(glm::ivec2 globalPosition);
    void DrawTilemap();
    void DrawTile(glm::vec2 position, Tile tile);
    //std::string is position stored as x,y and Tile is tile displayed at that position
    std::unordered_map<std::string, Tile> tilemap;
    std::unordered_map<std::string, Entity*> logicTilemap;
};