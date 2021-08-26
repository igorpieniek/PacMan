#pragma once
#include "GLBuffer.h"
#include <vector>

class IndexBuffer : public GLBuffer{
public:
	IndexBuffer(const unsigned int* indices, int count, uint16_t usage = GL_STATIC_DRAW);
	IndexBuffer(std::vector<unsigned int> indices, uint16_t usage = GL_STATIC_DRAW);

	void bind() const override;
	void unbind() const override;

	unsigned int getCount()const { return count; };

private:
	int count;

};

