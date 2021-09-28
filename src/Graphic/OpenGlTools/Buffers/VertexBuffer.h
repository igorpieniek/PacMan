#pragma once
#include "GLBuffer.h"
#include <vector>


class VertexBuffer :public GLBuffer{
public:
	VertexBuffer(const void* data, int size, uint16_t usage = GL_STATIC_DRAW);
	VertexBuffer(std::vector<float>& data, uint16_t usage = GL_STATIC_DRAW);

	void bind() const override;
	void unbind() const override;


	~VertexBuffer();

};

