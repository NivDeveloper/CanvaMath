#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    m_Vertices = std::move(vertices);
    m_Indices = std::move(indices);
}

void Mesh::SetMaterial(std::shared_ptr<Material> mat) {
    m_Material = mat;
}

void Mesh::SetModelMat(const glm::mat4& model) {
    m_Material->Bind();
    m_Material->SetModelMat(model);
    m_Material->Unbind();

}

void Mesh::Compile() {
    VBLayout vbl;
    vbl.push(3, GL_FLOAT);
    vbl.push(3, GL_FLOAT);
    vbl.push(2, GL_FLOAT);

    m_vbo.setData(&m_Vertices[0], m_Vertices.size()*8*sizeof(float));
    if (m_Indices.size() != 0) {
        m_ebo.setData(&m_Indices, m_Indices.size());
    }
    m_vao.addBuffer(m_vbo, vbl);

    //compile material
}

void Mesh::Draw() {
    m_vao.Bind();
    m_vbo.Bind();
    m_Material->Bind();
    
    if (m_Indices.size() == 0) {
        glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
    }
    else {
        m_ebo.Bind();
        glDrawElements(GL_TRIANGLES, m_ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
        m_ebo.Unbind();
    }
    m_Material->Unbind();
    m_vbo.Unbind();
    m_vao.Unbind();
}
