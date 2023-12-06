#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shader{
public:
    Shader() {}
    // takes in paths to vert and frag shader
    Shader(const std::string& vsPath, const std::string& fsPath);
    // deletes shader program
    ~Shader();

    void Bind()const;
    void Unbind()const;

    //set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
    void SetUniformVec3f(const std::string& name, float v0, float v1, float v2);
    void SetUniformVec3f(const std::string& name, const glm::vec3& vec);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void Compile();
private:
    unsigned int m_ID;
    std::string m_VertexSource;
    std::string m_FragmentSource;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name);
};

class CompShader {
private:
    unsigned int m_ID;
    unsigned int m_X, m_Y, m_Z;
    std::string m_CompSource;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name){return 0;}
public:
    CompShader() {}
    CompShader(const std::string& path, unsigned int x, unsigned int y, unsigned int z);
    void Execute();
    void Compile();
    void Bind();
    void Unbind();

};