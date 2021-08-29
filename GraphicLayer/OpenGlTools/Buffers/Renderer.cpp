#include "Renderer.h"

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
	shader.bind();
	va.bind();
	ib.bind();
	ERROR_CHECK(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib, const std::shared_ptr<Shader>& shader) const{
	shader->bind();
	va->bind();
	ib->bind();
	ERROR_CHECK(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const{
	glClear(GL_COLOR_BUFFER_BIT);
}
