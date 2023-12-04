#pragma once
#include <vector>
// #include <typeinfo>
#include "glad/glad.h"


/**
 * @brief Contains metadata of specific vertex element (e.g position/color)
 * to be used when setting attribute array
 */
struct VBElement{	
	//type of element stored
	unsigned int type;
	//number of these type of element
	unsigned int count;
	unsigned char normalized;

	//@return size of GLenum - data type of element 
	static unsigned int	GetSizeOfType(unsigned int type){
		switch (type){
            case GL_FLOAT:			return 4;
            case GL_UNSIGNED_INT:	return 4;
            case GL_UNSIGNED_BYTE:	return 1;
			case GL_INT:			return 4;
		}
		return 0;
	}
};

/**
 * @brief Layout of a single vertex
 * 
 */
class VBLayout{
private:
    //indices match with the location returned by glGetAttribLocation
	std::vector<VBElement> m_Elements;
	unsigned int m_Stride;

public:
    VBLayout() : m_Stride(0){ }

	// template<typename T>
	void push(unsigned int count, unsigned int type){
        VBElement v{ type, count, false };
		m_Elements.push_back(v);
		m_Stride += count * VBElement::GetSizeOfType(type);
    }

    

    const std::vector<VBElement>& GetElements() const& { return m_Elements; }
	unsigned int GetStride() const { return m_Stride; }

};

