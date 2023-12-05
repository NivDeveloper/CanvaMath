#include "Scene.h"
namespace scenes {
	
	SceneMenu::SceneMenu(Scene*& currentTestPointer)
		: m_CurrentScene(currentTestPointer) {
			m_ClearColor = {0.2f, 0.4f, 0.8f, 1.0f};
	}

	bool SceneMenu::OnUIRender() {
		for (auto& test : m_Scenes) {
			if (ImGui::Button(test.first.c_str())){
				m_CurrentScene = test.second();
				return true;
			}
		}
		return false;
	}

}