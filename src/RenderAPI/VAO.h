#pragma once

#include "VBLayout.h"
#include "VBO.h"
class VAO{
private:
    unsigned int m_ID;
    unsigned int m_vertCount;

public:
    VAO();
    ~VAO();
    void Bind()const;
    void Unbind()const;

    void addBuffer(const VBO& vbo, const VBLayout& vbl);
    unsigned int getVertexCount() const {return m_vertCount;}

};