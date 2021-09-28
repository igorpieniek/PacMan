#pragma once

#include <vector>
#include <GL/glew.h>
#include <assert.h>


struct VertexBufferElement {
	unsigned int type{};
	unsigned int count{};
	unsigned char normalized{};

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type){
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		assert(false);
		return 0;
	}
};


class VertexBufferLayout{
public:
	VertexBufferLayout()
		:stride(0) {};

	template<typename T>
	void push(unsigned int  count) {
		static_assert(false);
	};

	template<>
	void push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	};

	template<>
	void push<unsigned int>(unsigned int  count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	};

	template<>
	void push<unsigned char>(unsigned int  count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE});
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	};

	const std::vector<VertexBufferElement>&
		getElements() const { return elements; };

	unsigned int getStride() const { return stride; };
	
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride{};
};

