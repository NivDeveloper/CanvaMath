#pragma once
#include "RenderAPI.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <string>
#include <memory>
#include <map>

enum MaterialType {
    TPhong,
    PBR,
    Blank,
    Canvas,
    Light
};

/**
 * @brief Interface to represent the material uniforms
 * can either be type: phong or pbr
 * each type can either consist of vec3's for each element or a texture
*/
class UniformBuffer {
protected:
    std::vector<Texture*> m_textures;
    int m_texcount;
public:
    MaterialType m_type;
    virtual void SetUniforms(Shader* shad){ }
    virtual void Compile(){}
    virtual void Bind(){}
    virtual void Unbind(){}
};

class Phong: public UniformBuffer {
public:
    std::vector<std::string> diffuse;
    std::vector<std::string> specular;
    std::vector<std::string> ambient;
    std::vector<std::string> normal;
    std::vector<std::string> height;
    float shininess;
    void AddDiffuse(const std::string& diff_tex){diffuse.push_back(diff_tex);m_texcount++;}
    void AddAmbient(const std::string& amb_tex){ambient.push_back(amb_tex);m_texcount++;}
    void AddSpecular(const std::string& spec_tex){specular.push_back(spec_tex);m_texcount++;}
    void AddNormal(const std::string& normal_tex){normal.push_back(normal_tex);m_texcount++;}
    void AddHeight(const std::string& height_tex){height.push_back(height_tex);m_texcount++;}
    void SetShininess(float shin) {shininess = shin;}
private:
    void SetUniforms(Shader* shad) override;
    void Compile() override;
    void Bind() override;
    void Unbind() override;
};

class PBR: public UniformBuffer {
    void SetAlbedo(){}
    void SetNormal(){}
    void SetMetallic(){}
    void SetRoughness(){}
    void SetAO(){}
};

struct DirLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    void SetUniforms(Shader* shad, unsigned int index);
};

struct PointLight {    
    glm::vec3 position;    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;

    void SetUniforms(Shader* shad, unsigned int index);
}; 

class Material {
private:
    MaterialType m_type;
    Shader* m_shader;
    std::vector<std::shared_ptr<DirLight>> Dlights;
    std::vector<std::shared_ptr<PointLight>> Plights;
    std::shared_ptr<UniformBuffer> m_buffer;
    void SetUniforms();
public:
    Material();
    Material(MaterialType mattype);
    void SetShader(const std::string& vspath, const std::string& fspath);
    void SetModelMat(const glm::mat4& model);
    void AddLight(std::shared_ptr<DirLight> dlight);
    void AddLight(std::shared_ptr<PointLight> plight);
    void SetBuffer(std::shared_ptr<UniformBuffer> buff);
    void Compile();
    void Bind();
    void Unbind();
    friend class Renderer;
};


