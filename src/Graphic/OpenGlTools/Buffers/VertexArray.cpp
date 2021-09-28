#include "VertexArray.h"

VertexArray::VertexArray(){
	glGenVertexArrays(1, &id);
	bind();

}

VertexArray::~VertexArray(){
	glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const {
	glBindVertexArray(id);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& el = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, el.count, el.type, el.normalized, layout.getStride(), (const void*)offset);
		offset += el.count * VertexBufferElement::getSizeOfType(el.type);

	}
}
