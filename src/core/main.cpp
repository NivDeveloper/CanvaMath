#include "Window.h"
#include "Camera.h"
#include "Scene1.h"
#include "Scene.h"
#include "Renderer.h"
#include "DebugGL.h"
#include "Debug.h"

#include "UI.h"


#include <iostream>
#include <chrono>

int width = 1200;
int height = 900;

int main() {
    try{Window::Init();}
    catch(std::exception &exception){return -1;}

    try{Window window("CanvaMath", width, height);

    Camera2D cam;
    window.AddListener(&cam);
    Renderer renderer;
    UI ui(&window);
    std::chrono::high_resolution_clock clock;
    auto begin = clock.now();
    auto end = clock.now();
    std::chrono::duration<float> frameTime = end - begin;
    int fcounter = 0;
    EnableDebugOutput();


    // * ---------------------------------
    scenes::Scene* currentscene = nullptr;
    scenes::SceneMenu* menu = new scenes::SceneMenu(currentscene);
    currentscene = menu;
    menu->AddScene<scenes::Scene1>("Scene1!");
    renderer.Submit(currentscene, cam);
    renderer.setClearColor(0.1f, 0.2f, 0.9f, 1.0f);
    // * ---------------------------------
    // ! ###############
    while (!window.ShouldClose()) {

        // * Frame Time calculation--------
        end = clock.now();
        if (fcounter > 500) {
            frameTime = end-begin;
            fcounter = 0;
        }
        else{ fcounter++; }
        begin = clock.now();
        // * ------------------------------

        window.PollEvents();
        window.ProcessEvents();
        renderer.Clear();
        ui.NewFrame();

        // ! IMGUI ----------------------
        ImGui::Begin("CanvaMath");
        ImGui::Text("Frame Time :%f", frameTime.count());
        ImGui::Text("FPS: %f", 1.0f/frameTime.count());
        if (currentscene) {
            currentscene->OnUpdate(0.1f);
            if (currentscene != menu && ImGui::Button("<-")) {
                delete currentscene;
                currentscene = menu;
                renderer.Submit(menu, cam);
            }
            if (currentscene->OnUIRender()) {
                renderer.Submit(currentscene, cam);
            }
            
        }
        ImGui::End();
        // ! ----------------------------
        
        renderer.Render(cam);
        ui.Render();
        window.SwapBuffers();
    }
    // ! ###############


    ui.Destroy();

    }catch(std::exception &exception){std::cout << exception.what() << std::endl;}
   


    Window::Quit();
    return 0;
}