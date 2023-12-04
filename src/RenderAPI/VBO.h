#pragma once

class VBO{
private:
    unsigned int m_size;
    unsigned int m_ID;
public:
    VBO();
    VBO(const void* data, unsigned int size);
    ~VBO();

    void Bind() const;
    void Unbind() const;

    void setData(const void* data, unsigned int size);

    unsigned int getSize() const { return m_size; }
};