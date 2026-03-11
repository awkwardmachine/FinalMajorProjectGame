//
// Created by Nil on 06/03/2026.
//

#include <glad/glad.h>

#include "Engine/Renderer/Buffers/VertexArray.h"

namespace Engine {
    VertexArray::VertexArray() : rendererID_(0) { glGenVertexArrays(1, &rendererID_); }
    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &rendererID_); }

    void VertexArray::bind() const {
        glBindVertexArray(rendererID_);
        if (indexBuffer_)
            indexBuffer_->bind();
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void VertexArray::unbind() const { glBindVertexArray(0); }

    void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vb) {
        bind();
        vb->bind();

        glEnableVertexAttribArray(static_cast<unsigned int>(vertexBuffers_.size()));
        glVertexAttribPointer(static_cast<unsigned int>(vertexBuffers_.size()), 3, GL_FLOAT, GL_FALSE,
                              3 * sizeof(float), nullptr);
        vertexBuffers_.push_back(vb);
    }

    void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &ib) {
        bind();
        ib->bind();
        indexBuffer_ = ib;
    }
} // namespace Engine
