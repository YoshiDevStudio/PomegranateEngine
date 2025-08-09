#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <map>

#include "Engine.h"
#include "Texture2D.h"

class File
{
public:
    static void LoadPNGInFolder(std::string path);
    static void LoadPNG(std::string path);

    static std::map<std::string, Texture2D*> loadedTextures;
};