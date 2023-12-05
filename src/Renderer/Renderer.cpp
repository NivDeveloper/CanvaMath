#include "Renderer.h"

Renderer::Renderer(){
   glEnable(GL_DEPTH_TEST);

}

void Renderer::setClearColor(float x, float y, float z, float w) {
    glClearColor(x, y, z, w);
}

void Renderer::Submit(scenes::Scene* sc, Camera& cam) {
    m_scene = sc;
    
    m_uboCam.setSize(2*sizeof(glm::mat4) + sizeof(glm::vec3));
    m_uboCam.setData(0, sizeof(glm::mat4), (void*)cam.GetViewMatrix());
    m_uboCam.setData(sizeof(glm::mat4), sizeof(glm::mat4), (void*)cam.GetProjectionMatrix());
    m_uboCam.setData(2*sizeof(glm::mat4), sizeof(glm::vec3), (void*)cam.GetPosition());
    m_uboCam.Link(0);
    for (auto s: sc->m_sceneshapes){
        s->m_mesh->Compile();
        s->m_mesh->SetModelMat(s->transform);
    } 
}

void Renderer::Clear() const{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}

void Renderer::Render(Camera& cam) {
    m_uboCam.setData(0, sizeof(glm::mat4), cam.GetViewMatrix());
    m_uboCam.setData(sizeof(glm::mat4), sizeof(glm::mat4), cam.GetProjectionMatrix());
    m_uboCam.setData(2*sizeof(glm::mat4), sizeof(glm::vec3), cam.GetPosition());
    setClearColor(m_scene->m_ClearColor[0],m_scene->m_ClearColor[1],m_scene->m_ClearColor[2],m_scene->m_ClearColor[3]);
    for (auto s: m_scene->m_sceneshapes){
        s->m_mesh->SetModelMat(s->transform);
        s->m_mesh->Draw();
    }
}
