#pragma once

#include <map>
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
    void SetTile(glm::ivec2 globalPosition, Tile tile);
    Tile* GetTileAt(glm::ivec2 globalPosition);

    glm::ivec2 AlignPosToGrid(glm::ivec2 position);

    int tileSize = 16;
private:

    void DrawTilemap();
    void DrawTile(glm::vec2 position, Tile tile);
    //std::string is position stored as x,y and Tile is tile displayed at that position
    std::map<std::string, Tile> tilemap;
};