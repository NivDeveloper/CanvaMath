#include "Window.h"
#include <stdexcept>


void Window::Init() {
    if(SDL_Init(SDL_InitFlags::SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR,SDL_GetError());
        throw std::runtime_error("Could not Init SDl");
    }
}

void Window::Quit() {
    SDL_Quit();
}

Window::Window(const std::string & title, int width, int height)
    : m_window(SDL_CreateWindow(title.c_str(), width, height, 
        SDL_WindowFlags::SDL_WINDOW_RESIZABLE | SDL_WindowFlags::SDL_WINDOW_OPENGL),
        &SDL_DestroyWindow) {
    
    if (!m_window)
        throw std::runtime_error(SDL_GetError());
}