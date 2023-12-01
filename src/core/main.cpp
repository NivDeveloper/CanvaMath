#include "SDL.h"
#include "Window.h"
#include "glm/glm.hpp"

#include <iostream>

int width = 1200;
int height = 900;

int main() {
    try{
        Window::Init();
    }
    catch(std::exception &exception){
        return -1;
    }

    try{
    Window window("CanvaMath", width, height);

    
    bool running = true;

    // ! ###############
    while (!window.ShouldClose()) {
        window.PollEvents();
        glClearColor(0.0f, 0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.SwapBuffers();


    }
    // ! ###############

    }
    catch(std::exception &exception){
        std::cout << exception.what() << std::endl;
    }
   


    Window::Quit();
    return 0;
}