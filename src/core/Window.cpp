#include "Window.h"
#include "stb_image.h"
#include "SDL3_image/SDL_image.h"

#include <iostream>
#include <stdexcept>


void Window::Init() {
    if(SDL_Init(SDL_InitFlags::SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR,SDL_GetError());
        throw std::runtime_error("Could not Init SDl");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::Quit() {
    SDL_Quit();
}

Window::~Window() {
    SDL_GL_DeleteContext(m_glcontext);  
    SDL_DestroyWindow(m_window);
}

Window::Window(const std::string & title, int width, int height)
    : m_window(SDL_CreateWindow(title.c_str(), width, height, 
        SDL_WindowFlags::SDL_WINDOW_RESIZABLE | SDL_WindowFlags::SDL_WINDOW_OPENGL)) {
    
    if (!m_window){
        std::cout << "failed to load window" << std::endl;
        throw std::runtime_error(SDL_GetError());}

    m_glcontext = SDL_GL_CreateContext(m_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        std::cout << "failed to load GLAD" << std::endl;
        throw std::runtime_error("Failed to load GLAD");}


    // SDL_GL_MakeCurrent(m_window, m_glcontext);
    SDL_GL_SetSwapInterval(0);

    glViewport(0,0,width, height);

    SDL_Surface* icon = IMG_Load("../res/icons/icon.png");
    SDL_SetWindowIcon(m_window, icon);
    SDL_DestroySurface(icon);

}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

void Window::PollEvents() {
    SDL_Event event;

        while (SDL_PollEvent(&event))
            if (event.type == SDL_EventType::SDL_EVENT_QUIT)
                m_ShouldClose = true;
}