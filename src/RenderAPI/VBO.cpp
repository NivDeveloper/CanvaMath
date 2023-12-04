#include "VBO.h"
#include "glad/glad.h"
#include <iostream>

VBO::VBO(const void* data, unsigned int size): m_size(size){
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID); 
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    Unbind();
}

VBO::VBO()
{
    m_size = 0;
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    // Unbind();
}


VBO::~VBO(){
    glDeleteBuffers(1, &m_ID);
}

void VBO::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(const void* data, unsigned int size){
    m_size = size;
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    // Unbind();
}
