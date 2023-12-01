#pragma once
#include "SDL.h"
#include <memory>
#include <string>
#include "glad/glad.h"


class Window {
private:
    SDL_Window* m_window;
    bool m_ShouldClose = false;
    SDL_GLContext m_glcontext;
public:
    static void Init();
    static void Quit();
    Window(const std::string& title, int width, int height);
    ~Window();
    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() { return m_ShouldClose;}
};