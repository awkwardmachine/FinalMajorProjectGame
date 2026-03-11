//
// Created by Nil on 06/03/2026.
//

#include <glad/glad.h>

#include "Engine/Renderer/Buffers/VertexBuffer.h"

namespace Engine {
    VertexBuffer::VertexBuffer(const void *data, const size_t size) : rendererID_(0) {
        glGenBuffers(1, &rendererID_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &rendererID_); }

    void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererID_); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void VertexBuffer::setData(const void *data, const size_t size) const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
    }
} // namespace Engine
