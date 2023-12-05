#pragma once
#include "SDL.h"
#include <memory>
#include <string>
#include <vector>
#include "glad/glad.h"


class IEventListener {
public:
    IEventListener(){}
    virtual void FBcallback(int width, int height){}
    virtual void CursorPoscallback(double xpos, double ypos){}
    virtual int MouseButtoncallback(Uint8 btn, Uint8 state){ return 0;}
    virtual void Scrollcallback(double xoffset, double ypffset){}
    virtual void Keycallback(int key, int scancode, int action, int mods){}
    virtual void ProcessInput(){}
    const Uint8* KeyStates;
    float CursPosX, CursPosY;
};


class Window {
private:
    SDL_Window* m_window;
    bool m_ShouldClose = false;
    SDL_GLContext m_glcontext;
    inline static std::vector<IEventListener*> m_listeners;
    const Uint8* KeyStates;
    static bool* m_uibool;
public:
    static void Init();
    static void Quit();
    Window(const std::string& title, int width, int height);
    ~Window();
    void SwapBuffers();
    void AddListener(IEventListener* listener);
    void PollEvents();
    bool ShouldClose() { return m_ShouldClose;}
    void ProcessEvents();
    void SetUIBool(bool* uibool);
    SDL_Window* GetWindow() {return m_window;}
    SDL_GLContext GetGLContext(){return &m_glcontext;}
};