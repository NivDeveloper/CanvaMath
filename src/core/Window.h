#pragma once
#include "SDL.h"
#include <memory>
#include <string>

class Window {
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    bool m_ShouldClose;
public:
    static void Init();
    static void Quit();
    Window(const std::string& title, int width, int height);
    bool ShouldClose() { return m_ShouldClose;}
};