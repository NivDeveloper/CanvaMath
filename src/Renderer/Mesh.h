#pragma once
#include "Material.h"

#include <iostream>
#include <memory>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::shared_ptr<Material> m_Material;
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
    void Compile();
    void Draw();
public:
    Mesh(){}
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    void SetMaterial(std::shared_ptr<Material> mat);
    // void SetViewPos(const glm::vec3& viewpos);
    void SetModelMat(const glm::mat4& model);
    friend class Renderer;
};