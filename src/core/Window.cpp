#include "Window.h"
#include "stb_image.h"
#include "SDL3_image/SDL_image.h"
#include "imgui_impl_sdl3.h"

#include <iostream>
#include <stdexcept>

bool* Window::m_uibool;

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
    KeyStates = SDL_GetKeyboardState(nullptr);
}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

void Window::SetUIBool(bool* uibool) {
    Window::m_uibool = uibool;
    // TODO disable click when mouse in scene and under UI
}

void Window::AddListener(IEventListener* listener) {
    listener->KeyStates = KeyStates;
    m_listeners.push_back(listener);
}

void Window::ProcessEvents() {
    for (auto l: m_listeners) {
        l->ProcessInput();
    }
}

void Window::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        ImGui_ImplSDL3_ProcessEvent(&event);
        switch(event.type) {
            case SDL_EVENT_QUIT:
                m_ShouldClose = true;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                for (auto l: m_listeners) {
                    l->CursorPoscallback(event.motion.x, event.motion.y);
                }
                break;
            case SDL_EVENT_KEY_DOWN:
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (*m_uibool)
                    break;
                for (auto l: m_listeners) {
                    SDL_GetMouseState(&l->CursPosX, &l->CursPosY);
                    int enable = l->MouseButtoncallback(event.button.button, event.button.state);
                    if (enable == 1) {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    else if (enable == -1) {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                    }
                }
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                for (auto l: m_listeners) {
                    SDL_GetMouseState(&l->CursPosX, &l->CursPosY);
                    l->Scrollcallback(event.wheel.x, event.wheel.y);
                }
                break;
                
            default:
                break;
        }
    }
}