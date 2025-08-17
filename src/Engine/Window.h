#pragma once

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Core.h"
#include "Input.h"
#include "Time_Utils.h"

class DLL_API Window
{
public:
    Window(std::string title, int width, int height, SDL_WindowFlags windowFlags = 0);
    ~Window();

    //!!TODO: Implement Mouse Events
    bool HandleEvent(SDL_Event* event);
    void FrameUpdate();

    void SetTitle(std::string title);
    std::string GetTitle();

    SDL_WindowFlags GetWindowFlags();

    void SetWindowSize(glm::ivec2 rect);
    void SetWindowSize(int width, int height);
    glm::ivec2 GetWindowSize();

    void SetWindowResizable(bool isResizable);
    void SetWindowFullscreen(bool isFullscreen);

    static SDL_Window* sdlWindow;
    static SDL_Renderer* renderer;

    glm::vec3 clearColor = glm::vec3(0.5f);
private:
    std::string title;

    SDL_WindowFlags windowFlags = 0;
    glm::ivec2 windowSize = glm::ivec2(0, 0);
    //Used for calculating deltaTime
    float prevTime = 0;
};