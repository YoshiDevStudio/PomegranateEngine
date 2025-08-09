#include "File.h"

std::map<std::string, Texture2D*> File::loadedTextures;


void File::LoadPNGInFolder(std::string path)
{
    for(const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + path))
    {
        std::string outFileName = entry.path().string();
        if(outFileName.ends_with(".png"))
        {
            LoadPNG(outFileName);
        }
    }
}

void File::LoadPNG(std::string path)
{
    SDL_IOStream* fs = SDL_IOFromFile(path.c_str(), "r");
    if(fs == nullptr)
    {
        LOG_ERROR("Could not open file: " + path);
        return;
    }
    SDL_Surface* surface = IMG_LoadPNG_IO(fs);
    if(surface == nullptr)
    {
        LOG_ERROR("Couldn't load bitmap at path: " + path);
        SDL_CloseIO(fs);
        SDL_DestroySurface(surface);
        return;
    }
    SDL_CloseIO(fs);

    Texture2D* tex2D = new Texture2D(surface->w, surface->h);
    if(Window::renderer == nullptr)
        LOG_ERROR("Renderer is nullptr");
    tex2D->texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(tex2D->texture == nullptr)
    {
        LOG_ERROR("Couldn't create static texture: " + std::string(SDL_GetError()));
        return;
    }

    SDL_DestroySurface(surface);

    path = path.substr(path.find_last_of("\\") + 1);

    loadedTextures.emplace(path, tex2D);
}