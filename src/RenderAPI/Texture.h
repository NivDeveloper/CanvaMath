#pragma once
#include <string>

enum TexType {
	png,
	jpg
};


class Texture{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	TexType m_type;
public:
	Texture(const std::string& path);
	Texture(const int width, const int height);
	~Texture();

	void Bind(unsigned int slot) const;
	void Unbind() const;
	void Compile();

	unsigned int id;
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};