#pragma once

#include "GLBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray : public GLBuffer{
public:
	VertexArray();
	~VertexArray();
	void bind() const override;
	void unbind() const override;

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

