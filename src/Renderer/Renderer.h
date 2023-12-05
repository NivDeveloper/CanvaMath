#pragma once
#include "RenderAPI.h"
#include "Camera.h"
#include "Scene.h"
#include "Shapes.h"
#include <vector>

class Renderer{
private:
    scenes::Scene* m_scene;
    UBO m_uboCam;
public:
    Renderer();
    void setClearColor(float x, float y, float z, float w);
    void Submit(scenes::Scene* scene, Camera& cam);
    void Clear() const;
    // void Draw(const VAO& vao, const Shader& shad);
    // void Draw(const VAO& va, const EBO& ebo, const Shader& shader) const;
    void Render(Camera& camera);
};