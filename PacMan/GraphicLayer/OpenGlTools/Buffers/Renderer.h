#pragma once

#include <GL/glew.h>
#include "shaderTools.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer {
public:
	void draw(const VertexArray& va, 
			  const IndexBuffer& ib, 
			  const Shader& shader ) const;
	void draw(const std::shared_ptr<VertexArray> va,
			  const std::shared_ptr<IndexBuffer> ib,
		      const std::shared_ptr<Shader> shader) const;

	void clear()const;
private:

};