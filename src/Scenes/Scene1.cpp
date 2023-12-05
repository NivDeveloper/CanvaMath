#include "Scene1.h"

namespace scenes {

    Scene1::Scene1() {
        m_ClearColor = {0.2, 0.4, 0.8, 1.0};
    }

    bool Scene1::OnUIRender() {

        
        ImGui::ColorPicker4("asd", &m_ClearColor[0]);
        return false;
    }


}