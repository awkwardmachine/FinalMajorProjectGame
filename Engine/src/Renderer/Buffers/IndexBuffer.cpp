//
// Created by Nil on 10/03/2026.
//

#include <glad/glad.h>

#include "Engine/Renderer/Buffers/IndexBuffer.h"

namespace Engine {
    IndexBuffer::IndexBuffer(const unsigned int *indices, const size_t count) :
        rendererID_(0), count_(static_cast<unsigned int>(count)) {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count_ * sizeof(unsigned int)), indices,
                     GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &rendererID_); }

    void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
} // namespace Engine
