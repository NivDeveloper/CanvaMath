#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <iostream>


Texture::Texture(const int wid, const int height)
	: m_RendererID(0), m_Width(wid), m_Height(height)
{
	/*Creates the stated number of Textures*/
	glGenTextures(1, &m_RendererID);
	// glBindTexture(GL_TEXTURE_2D, m_RendererID);
	Bind(0);
	// id = m_RendererID;
	/*sets the stated parameter of the given texture to the given parameter*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, wid, height, 0, GL_RGBA, 
             GL_FLOAT, NULL);
	// glGenerateMipmap(GL_TEXTURE_2D);
	glBindImageTexture(0, m_RendererID, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
}

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	if (path.substr(path.size() - 3) == "png") {
		m_type = png;
	}
	else if (path.substr(path.size() - 3) == "jpg") {
		m_type = jpg;
	}
	
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

	if (!m_LocalBuffer) {
		std::cout << "Failed to load texture " << path << std::endl;
	}
}

void Texture::Compile(){
	
	/*Creates the stated number of Textures*/
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	// id = m_RendererID;

	/*sets the stated parameter of the given texture to the given parameter*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	//opengl starts (0,0) at bottom left so we need to flip image

	if (m_LocalBuffer) {
		switch (m_type)
		{
		case png:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
			break;
		case jpg:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
			break;
		default:
			break;
		}
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot/*=0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}