#pragma once

class UBO{
private:
    unsigned int m_ID;
    unsigned int m_size;

public:
	UBO();
	UBO(unsigned int size);
	~UBO();

	void Bind() const;
	void Unbind() const;
    void Link(unsigned int bindpoint);

	// inline unsigned int GetCount() const { return m_count; }
	void setData(unsigned int offset,  unsigned int size, void* data);
    void setSize(unsigned int size);
};