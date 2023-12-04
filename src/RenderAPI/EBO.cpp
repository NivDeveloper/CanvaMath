#include "EBO.h"
#include "glad/glad.h"
#include <iostream>

EBO::EBO(const unsigned int* data, unsigned int count): m_count(count){
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


EBO::EBO() {
    m_count = 0;
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

EBO::~EBO(){
    glDeleteBuffers(1, &m_ID);
}

void EBO::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setData(const void* data, unsigned int count) {
    m_count = count;
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}