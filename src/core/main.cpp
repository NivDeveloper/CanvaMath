#include "SDL.h"
#include "Window.h"

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
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event))
            if (event.type == SDL_EventType::SDL_EVENT_QUIT)
                running = false;


    }
    // ! ###############

    }
    catch(std::exception &exception){
        std::cout << exception.what() << std::endl;
    }
   


    Window::Quit();
    return 0;
}