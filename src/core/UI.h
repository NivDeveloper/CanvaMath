#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"

class UI {
public:
    ImGuiIO* io;
    UI(Window* window);
    Window* window;
    void NewFrame();
    void Render();
    void Destroy();
};