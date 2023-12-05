#pragma once
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include "imgui.h"

#include "Texture.h"
#include "Shapes.h"
#include "Material.h"

namespace scenes {
	class Scene
	{
	public:
		Scene(){}
		virtual ~Scene(){}
		virtual void OnUpdate(float deltaTime){ }
		virtual void OnRender(){ }
		virtual bool OnUIRender() {return false;}
		int m_scrW = 1200;
		int m_scrH = 900;

		std::vector<shapes::Shape*> m_sceneshapes;
		std::vector<float> m_ClearColor;
	};

	class SceneMenu : public Scene
	{
	public:
		SceneMenu(Scene*& currentTestPointer);
		bool OnUIRender() override;

		template<typename T>
		void AddScene(const std::string& name)
		{
			std::cout << "Adding Scene" << name << std::endl;
			m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		//reference to pointer so that current test can be changed
		Scene*& m_CurrentScene;
		std::vector<std::pair<std::string, std::function<Scene* ()>>> m_Scenes;
	};
}