#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Core.h"
#include "Texture2D.h"
#include "Animation.h"
#include "Tile.h"

class DLL_API File
{
public:
    static std::vector<Texture2D*> LoadPNGInFolder(std::string folderPath);
    static Texture2D* LoadPNG(std::string filePath);

    static std::vector<Tile> LoadTilemap(std::string filePath, int tileSize);
    static Tile GetTileAtPos(std::string tilemapName, glm::ivec2 position);
    static Animation* LoadAnimation(std::string folderPath);

    static void UnloadTexture(std::string textureName);
    static void UnloadTexture(Texture2D* texture);
    static void Uninitialize();

    static std::string GetFileName(std::string absolutePath);
    static std::string RemoveFileDirectory(std::string path);
    static std::string RemoveFileExtension(std::string path);

    //Here is where all loaded textures are stored, you can get them by inputting the filename without its extension
    static std::map<std::string, Texture2D*> loadedTextures;
    //All loaded tiles are stored here, first is the name of the tilemap you are accessing, second is the tiles loaded from the given tilemap
    static std::map<std::string, std::vector<Tile>> loadedTiles;
};