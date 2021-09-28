#pragma once

#include <GL/glew.h>
#include "ShaderTools.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer {
public:
	void draw(const VertexArray& va, 
			  const IndexBuffer& ib ) const;
	void draw(const std::shared_ptr<VertexArray>& va,
			  const std::shared_ptr<IndexBuffer>& ib) const;

	void clear()const;
};