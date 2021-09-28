#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* indices, int count, uint16_t usage):
	count(count)
{
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, usage);
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> indices, uint16_t usage)
	: IndexBuffer(indices.data(), indices.size(), usage) {};

void IndexBuffer::bind()const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind()const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
