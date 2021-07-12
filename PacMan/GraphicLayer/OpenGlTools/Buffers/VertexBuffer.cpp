#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, int size, uint16_t usage) {
    ERROR_CHECK(glGenBuffers(1, &id));
    bind();
    ERROR_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage) );
}

VertexBuffer::VertexBuffer(std::vector<float>& data,  uint16_t usage) :
    VertexBuffer(data.data(), data.size()* sizeof(float), usage) {
}


VertexBuffer::~VertexBuffer() {
    ERROR_CHECK(glDeleteBuffers(1, &id));
}



void VertexBuffer::bind()const {
    ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unbind()const {
    ERROR_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}




