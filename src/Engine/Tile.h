#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "Core.h"
#include "Texture2D.h"
#include "Transform2D.h"

class DLL_API Tile
{
public:
    //texturePosition is relative to texture coordinates
    Tile(glm::ivec2 texturePosition, Texture2D* tex2D = nullptr, int tileSize = 0, bool hasCollision = false, int zIndex = 0, bool isReplaceable = true)
    {
        this->texturePosition = texturePosition;
        this->tex2D = tex2D;
        this->tileSize = tileSize;
        this->hasCollision = hasCollision;
        this->zIndex = zIndex;
        this->isReplaceable = isReplaceable;
    }

    void Copy(Tile otherTile)
    {
        this->texturePosition = otherTile.texturePosition;
        this->tex2D = otherTile.tex2D;
        this->tileSize = otherTile.tileSize;
        this->hasCollision = otherTile.hasCollision;
        this->zIndex = otherTile.zIndex;
        this->isReplaceable = otherTile.isReplaceable;
    }
    
    glm::ivec2 position;
    glm::ivec2 texturePosition;
    Texture2D* tex2D;
    int tileSize;
    bool hasCollision;
    int zIndex;
    bool isReplaceable;
};