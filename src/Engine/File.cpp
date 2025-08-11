#include "File.h"

std::map<std::string, Texture2D*> File::loadedTextures;

//Loads all PNGs in path and stores them in File::loadedTextures
void File::LoadPNGInFolder(std::string folderPath)
{
    try
    {
        for(const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + folderPath))
        {
            std::string outFileName = entry.path().string();
            if(outFileName.ends_with(".png"))
            {
                LoadPNG(outFileName);
            }
        }
    }
    catch(std::exception e)
    {
        LOG_ERROR(e.what());
    }
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

//Loads all images in folder and converts them into an animation
//Images are loaded in alphabetical order
//Images must be .png
Animation* File::LoadAnimation(std::string folderPath)
{
    try
    {
        Animation* animation = new Animation();
        for(const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + folderPath))
        {
            std::string outFileName = entry.path().string();
            if(outFileName.ends_with(".png"))
            {
                Texture2D* tex = LoadPNG(outFileName);
                animation->AddFrame(tex);
            }
        }
        return animation;
    }
    catch(std::exception e)
    {
        LOG_ERROR(e.what());
    }
    return nullptr;
}

void File::Uninitialize()
{
    for(const auto& pair : loadedTextures)
    {
        delete pair.second;
    }
}