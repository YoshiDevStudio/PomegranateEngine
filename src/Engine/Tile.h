#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "DLL_Build.h"
#include "Texture2D.h"

class DLL_API Tile
{
public:
    //tilePosition is relative to texture coordinates
    Tile(glm::ivec2 texturePosition, Texture2D* tex2D = nullptr, int tileSize = 0, int zIndex = 0, bool isReplaceable = true)
    {
        this->texturePosition = texturePosition;
        this->tex2D = tex2D;
        this->tileSize = tileSize;
        this->zIndex = zIndex;
        this->isReplaceable = isReplaceable;
    }
    
    glm::ivec2 position;
    glm::ivec2 texturePosition;
    Texture2D* tex2D;
    int tileSize;
    int zIndex;
    bool isReplaceable;
};