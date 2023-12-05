#include "Renderer.h"

Renderer::Renderer(){}

void Renderer::setClearColor(float x, float y, float z, float w) {
    glClearColor(x, y, z, w);
}

void Renderer::Submit(scenes::Scene* sc, Camera& cam) {m_scene = sc;}

void Renderer::Clear() const{ glClear(GL_COLOR_BUFFER_BIT);}

void Renderer::Render(Camera& cam) {
    setClearColor(m_scene->m_ClearColor[0], m_scene->m_ClearColor[1], m_scene->m_ClearColor[2], m_scene->m_ClearColor[3]);
}
