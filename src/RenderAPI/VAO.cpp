#include "glad/glad.h"
#include "VAO.h"
#include <vector>
#include <iostream>



VAO::VAO(){
    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
	m_vertCount = 0;
	Bind();
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &m_ID);
}

void VAO::Bind()const{
    glBindVertexArray(m_ID);
}

void VAO::Unbind()const{
    glBindVertexArray(0);
}

void VAO::addBuffer(const VBO& vbo, const VBLayout& vbl){ 
	Bind();
	vbo.Bind();
	m_vertCount += vbo.getSize()/vbl.GetStride();
	const auto& elements = vbl.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); ++i){
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vbl.GetStride(), (const void*)offset);
		offset += element.count * VBElement::GetSizeOfType(element.type);
	}
	// vbo.Unbind();

}


