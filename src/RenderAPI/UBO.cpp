#include "UBO.h"
#include "glad/glad.h"

UBO::UBO(unsigned int size): m_size{size} {
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
    glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STATIC_DRAW);
    Unbind();
}

UBO::UBO() {
    m_size = 0;
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
}

void UBO::setSize(unsigned int size) {
    m_size = size;
    Bind();
    glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STATIC_DRAW);
    Unbind();
}

void UBO::Bind() const{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
}

void UBO::Unbind() const{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UBO::~UBO(){
    glDeleteBuffers(1, &m_ID);
}

void UBO::Link(unsigned int bindpoint) {
    Bind();
    glBindBufferBase(GL_UNIFORM_BUFFER, bindpoint, m_ID);
    Unbind();
}

void UBO::setData(unsigned int offset, unsigned int size, void* data) {
    Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    Unbind();
}