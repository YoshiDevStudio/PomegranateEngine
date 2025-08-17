#include "File.h"

std::map<std::string, Texture2D*> File::loadedTextures;
std::map<std::string, std::vector<Tile>> File::loadedTiles;

//Loads all PNGs in path and stores them in File::loadedTextures
std::vector<Texture2D*> File::LoadPNGInFolder(std::string folderPath)
{
    std::vector<Texture2D*> textures;
    try
    {
        for(const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + folderPath))
        {
            std::string outFileName = entry.path().string();
            if(outFileName.ends_with(".png"))
            {
                textures.push_back(LoadPNG(outFileName));
            }
        }
        return textures;
    }
    catch(std::exception e)
    {
        LOG_ERROR(e.what());
    }
    return textures;
}

//Loads PNG in path and stores it in File::loadedTextures
Texture2D* File::LoadPNG(std::string filePath)
{
    SDL_IOStream* fs = SDL_IOFromFile(filePath.c_str(), "r");
    if(fs == nullptr)
    {
        LOG_ERROR("Could not open file: " + filePath);
        return nullptr;
    }
    SDL_Surface* surface = IMG_LoadPNG_IO(fs);
    if(surface == nullptr)
    {
        LOG_ERROR("Couldn't load bitmap at path: " + filePath);
        SDL_CloseIO(fs);
        SDL_DestroySurface(surface);
        return nullptr;
    }
    SDL_CloseIO(fs);

    Texture2D* tex2D = new Texture2D(surface->w, surface->h);
    if(Window::renderer == nullptr)
        LOG_ERROR("Renderer is nullptr");
    tex2D->texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(tex2D->texture == nullptr)
    {
        LOG_ERROR("Couldn't create static texture: " + std::string(SDL_GetError()));
        return nullptr;
    }

    SDL_DestroySurface(surface);

    //remove directory path, only filename
    filePath = filePath.substr(filePath.find_last_of("\\") + 1);
    //remove file extension
    filePath.erase(filePath.end() - 4, filePath.end());
    loadedTextures.emplace(filePath, tex2D);
    LOG_VERBOSE("Loaded Texture: " + filePath);
    return tex2D;
}

//Loads PNG image and splits it up into Tiles of size: tileSize
std::vector<Tile> File::LoadTiles(std::string filePath, int tileSize)
{
    std::vector<Tile> tiles;
    Texture2D* tilemap = LoadPNG(filePath);
    for(int y = 0; y < tilemap->size.y; y += tileSize)
    {
        for(int x = 0; x < tilemap->size.x; x += tileSize)
        {
            Tile tile(glm::ivec2(x, y), tilemap, tileSize);
            tiles.push_back(tile);
        }
    }
    loadedTiles.emplace(GetFileName(filePath), tiles);
    return tiles;
}

//Get Tile from tilemap at position given
Tile File::GetTileAtPos(std::string tilemapName, glm::ivec2 position)
{
    std::vector<Tile> tiles = File::loadedTiles[tilemapName];
    //Tilemap is split into chunks of size: tileSize, so divide height by tileSize to be within bounds of array
    return tiles[position.y * (tiles[0].tex2D->size.y / tiles[0].tileSize) + position.x];
}

//Loads all images in folder and converts them into an animation
//Images are loaded in alphabetical order
//Images must be .png
Animation* File::LoadAnimation(std::string folderPath)
{
    std::vector<Texture2D*> textures = LoadPNGInFolder(folderPath);
    Animation* animation = new Animation();
    for(int i = 0; i < textures.size(); i++)
    {
        animation->AddFrame(textures[i]);
    }
    return animation;
}

void UnloadTexture(std::string textureName)
{
    for(const auto& pair : File::loadedTextures)
    {
        if(textureName == pair.first)
        {
            delete pair.second;
            File::loadedTextures.erase(textureName);
        }
    }
}

void UnloadTexture(Texture2D* texture)
{
    for(const auto& pair : File::loadedTextures)
    {
        if(texture == pair.second)
        {
            delete pair.second;
            File::loadedTextures.erase(pair.first);
        }
    }
}

void File::Uninitialize()
{
    for(const auto& pair : File::loadedTextures)
    {
        delete pair.second;
    }
}

std::string File::GetFileName(std::string absolutePath)
{
    absolutePath = RemoveFileDirectory(absolutePath);
    absolutePath = RemoveFileExtension(absolutePath);

    return absolutePath;
}

std::string File::RemoveFileDirectory(std::string path)
{
    int lastSlash = path.find_last_of("\\");
    if(lastSlash != std::string::npos)
        path = path.substr(lastSlash + 1);
    else
        lastSlash = path.find_last_of("/");
    if(lastSlash != std::string::npos)
        path = path.substr(lastSlash + 1);
    return path;
}

std::string File::RemoveFileExtension(std::string path)
{
    int lastDot = path.find_last_of(".");
    if(lastDot != std::string::npos)
        path.erase(path.begin() + path.find_last_of("."), path.end());
    return path;
}