#pragma once


class EBO{
private:
    unsigned int m_ID;
    unsigned int m_count;

public:
	EBO();
	EBO(const unsigned int* data, unsigned int count);
	~EBO();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }
	void setData(const void* data, unsigned int size);
};