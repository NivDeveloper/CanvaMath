#include "Material.h"

Material::Material() { }
Material::Material(MaterialType mattype): m_type{mattype} {
    //set shader
    if (mattype == TPhong) {
        m_shader = new Shader("../src/Shaders/Phong/phong.vert", "../src/Shaders/Phong/phong.frag");
    }
    else if (mattype == Blank) {
        m_shader = new Shader("../src/Shaders/default.vert", "../src/Shaders/default.frag");
    }
    else if (mattype == Canvas) {
        m_shader = new Shader("../src/Shaders/default.vert", "../src/Shaders/mandelbrot.frag");
    }
    else if (mattype == Light) {
        m_shader = new Shader("../src/Shaders/Phong/phong.vert", "../src/Shaders/Phong/lightsource.frag");
    }
}

// void Material::AddTexture(const std::string& path) {
//     m_Textures.push_back(new Texture(path));
// }

void Material::AddLight(std::shared_ptr<DirLight> dlight) {
    Dlights.push_back(dlight);
}

void Material::AddLight(std::shared_ptr<PointLight> plight) {
    Plights.push_back(plight);
}

void Material::SetBuffer(std::shared_ptr<UniformBuffer> buff) {
    m_buffer = buff;
}

void Material::SetShader(const std::string& vspath, const std::string& fspath) {
    m_shader = new Shader(vspath, fspath);
}

void Material::SetCompShader(const std::string& path, unsigned int x, unsigned int y, unsigned int z) {
    m_comp = new CompShader(path, x, y, z);
}

void Material::SetCompTex(const int width, const int height) {
    m_compTexture = new Texture(width, height);
}



void Material::SetUniforms() {
    if (m_type == TPhong) {
        // set all light uniforms
        for (size_t i = 0; i < Dlights.size(); i++) {
            Dlights[i]->SetUniforms(m_shader, i);
        }
        for (size_t i = 0; i < Plights.size(); i++) {
            Plights[i]->SetUniforms(m_shader, i);
        }
    }
}

void Material::SetModelMat(const glm::mat4& model) {
    m_shader->SetUniformMat4f("model", model);
}

void Material::Compile() {
    m_shader->Compile();
    if (m_type == TPhong){
        m_buffer->Compile();
    }

    m_comp->Compile();
}

void Material::Bind() {
    m_shader->Bind();
    if (m_type == TPhong) {
        m_buffer->SetUniforms(m_shader);
        m_buffer->Bind();
    }
    SetUniforms();

    // TODO comp rendering shouldnt be here
    m_compTexture->Bind(0);
    // m_comp->Execute();

}

void Material::Execute() {
    // m_compTexture->Bind(0);
    m_comp->Bind();
    m_comp->Execute();
    m_comp->Unbind();
    // m_compTexture->Unbind();
}

void Material::Unbind() {
    m_shader->Unbind();
    if (m_type == TPhong) {
        m_buffer->Unbind();
    }

    // m_compTexture->Unbind();
    // m_comp->Bind();
}

void Phong::SetUniforms(Shader* shad) {
    int index = 0;
    for (size_t i = 0; i < diffuse.size(); i++) {
        shad->SetUniform1i("material.diffuse", index);
        index++;
    }
    for (size_t i = 0; i < specular.size(); i++) {
        shad->SetUniform1i("material.specular", index);
        index++;
    }
    for (size_t i = 0; i < ambient.size(); i++) {
        shad->SetUniform1i("material.ambient", index);
        index++;
    }
    for (size_t i = 0; i < normal.size(); i++) {
        shad->SetUniform1i("material.normal", index);
        index++;
    }
    for (size_t i = 0; i < height.size(); i++) {
        shad->SetUniform1i("material.height", index);
        index++;
    }
}

void Phong::Compile() {
    for (size_t i = 0; i < diffuse.size(); i++) {
        m_textures.push_back(new Texture(diffuse[i]));
    }
    for (size_t i = 0; i < specular.size(); i++) {
        m_textures.push_back(new Texture(specular[i]));
    }
    for (size_t i = 0; i < ambient.size(); i++) {
        m_textures.push_back(new Texture(ambient[i]));
    }
    for (size_t i = 0; i < normal.size(); i++) {
        m_textures.push_back(new Texture(normal[i]));
    }
    for (size_t i = 0; i < height.size(); i++) {
        m_textures.push_back(new Texture(height[i]));
    }

    for (auto t: m_textures) {
        t->Compile();
    }
}

void Phong::Bind() {
    for (size_t i = 0; i < m_textures.size(); i++)
        m_textures[i]->Bind(i);
}

void Phong::Unbind() {
    for (size_t i = 0; i < m_textures.size(); i++)
        m_textures[i]->Unbind();
}

void DirLight::SetUniforms(Shader* shad, unsigned int index) {
    shad->SetUniformVec3f("dlights[" + std::to_string(index) + "].direction", direction);
    shad->SetUniformVec3f("dlights[" + std::to_string(index) + "].ambient", ambient);
    shad->SetUniformVec3f("dlights[" + std::to_string(index) + "].diffuse", diffuse);
    shad->SetUniformVec3f("dlights[" + std::to_string(index) + "].specular", specular);
}

void PointLight::SetUniforms(Shader* shad, unsigned int index) {
    shad->SetUniformVec3f("plights[" + std::to_string(index) + "].position", position);
    shad->SetUniformVec3f("plights[" + std::to_string(index) + "].ambient", ambient);
    shad->SetUniformVec3f("plights[" + std::to_string(index) + "].diffuse", diffuse);
    shad->SetUniformVec3f("plights[" + std::to_string(index) + "].specular", specular);
    shad->SetUniform1f("plights[" + std::to_string(index) + "].constant", constant);
    shad->SetUniform1f("plights[" + std::to_string(index) + "].linear", linear);
    shad->SetUniform1f("plights[" + std::to_string(index) + "].quadratic", quadratic);
}