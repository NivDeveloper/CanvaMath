#include "Shader.h"
#include "glad/glad.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Shader::Shader(const std::string& vsPath, const std::string& fsPath){

    // Parse Shaders------
    std::ifstream vsfile;
    std::ifstream fsfile;

    vsfile.open(vsPath.c_str());
    fsfile.open(fsPath.c_str());

    if(!vsfile.is_open()) std::cout << "failed to open " << vsPath << std::endl;
    if(!fsfile.is_open()) std::cout << "failed to open " << fsPath << std::endl;

    std::stringstream vsstream;
    std::stringstream fsstream;

    vsstream << vsfile.rdbuf();
    fsstream << fsfile.rdbuf();

    m_VertexSource = vsstream.str();
    m_FragmentSource = fsstream.str();

    vsfile.close();
    fsfile.close();
}

void Shader::Compile() {
    const char* vsSource = m_VertexSource.c_str();
    const char* fsSource = m_FragmentSource.c_str();

    // -------------------
    // Create OpenGL shader programs--------
    m_ID = glCreateProgram();

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSource, nullptr);
    glShaderSource(fs, 1, &fsSource, nullptr);

    glCompileShader(vs);
    glCompileShader(fs);
    // ------------------------------------

    // Error handling-----
    int resultv;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &resultv);
    if (resultv == GL_FALSE)
    {
        int length;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(vs, length, &length, message);

        std::cout << "Failed to compile vertex shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(vs);
    }
    int resultf;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &resultf);
    if (resultf == GL_FALSE)
    {
        int length;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(fs, length, &length, message);

        std::cout << "Failed to compile fragment shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(fs);
    }
    // ------------------

    glAttachShader(m_ID, vs);
    glAttachShader(m_ID, fs);
    //read docs
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);

    glDeleteShader(vs);
    glDeleteShader(fs);

    Bind();
}

Shader::~Shader(){ glDeleteProgram(m_ID); }
void Shader::Bind()const{ glUseProgram(m_ID); }
void Shader::Unbind()const{ glUseProgram(0); }

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    }
    m_UniformLocationCache[name] = location;

    return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);

}
void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformVec3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniformVec3f(const std::string& name, const glm::vec3& vec) {
    glUniform3f(GetUniformLocation(name),vec[0], vec[1], vec[2]);
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

CompShader::CompShader(const std::string& path, unsigned int x, unsigned int y, unsigned int z)
    :m_X{x}, m_Y{y}, m_Z{z}
{
    // Parse Shaders------
    std::ifstream compfile;

    compfile.open(path.c_str());

    if(!compfile.is_open()) std::cout << "failed to open " << path << std::endl;

    std::stringstream compstream;

    compstream << compfile.rdbuf();

    m_CompSource = compstream.str();

    compfile.close();
}

void CompShader::Compile() {
    const char* compsource = m_CompSource.c_str();

    m_ID = glCreateProgram();
    unsigned int cmp = glCreateShader(GL_COMPUTE_SHADER);

    glShaderSource(cmp, 1, &compsource, nullptr);

    glCompileShader(cmp);
    
    // ------------------------------------

    // Error handling-----
    int resultv;
    glGetShaderiv(cmp, GL_COMPILE_STATUS, &resultv);
    if (resultv == GL_FALSE)
    {
        int length;
        glGetShaderiv(cmp, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(cmp, length, &length, message);

        std::cout << "Failed to compile compute shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(cmp);
    }

    glAttachShader(m_ID, cmp);
    //read docs
    glLinkProgram(m_ID);
    glValidateProgram(m_ID);

    glDeleteShader(cmp);
}

void CompShader::Bind() {
    glUseProgram(m_ID);
}
void CompShader::Unbind() {
    glUseProgram(0);
}

void CompShader::Execute() {
    Bind();
    glDispatchCompute(m_X, m_Y, m_Z);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    Unbind();
}