#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <map>

#include "Core.h"
#include "Texture2D.h"
#include "Animation.h"

class DLL_API File
{
public:
    static void LoadPNGInFolder(std::string folderPath);
    static Texture2D* LoadPNG(std::string filePath);

    static Animation* LoadAnimation(std::string folderPath);

    static void Uninitialize();

    //Here is where all loaded textures are stored, you can get them by inputting the filename without its extension
    static std::map<std::string, Texture2D*> loadedTextures;
};