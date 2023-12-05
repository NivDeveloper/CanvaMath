#include "Scene1.h"
#include "Shapes.h"

namespace scenes {

    Scene1::Scene1() {
        m_ClearColor = {0.2, 0.4, 0.8, 1.0};
        auto rec = new shapes::Rectangle(glm::mat4(1.0f), glm::vec3(0.0f));
        auto mat = std::make_shared<Material>(Canvas);
        mat->SetShader("../src/Shaders/default.vert", "../src/Shaders/mandelbrot.frag");
        mat->Compile();
        rec->SetMaterial(mat);
        m_sceneshapes.push_back(rec);
        
    }

    bool Scene1::OnUIRender() {

        
        ImGui::ColorPicker4("asd", &m_ClearColor[0]);
        return false;
    }


}