#pragma once

#include <memory>
#include <vector>

#include "Engine/Core/DLLExports.h"
#include "Engine/Renderer/Buffers/IndexBuffer.h"
#include "Engine/Renderer/Buffers/VertexBuffer.h"

namespace Engine {
    class ENGINE_API VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;
        void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vb);
        void setIndexBuffer(const std::shared_ptr<IndexBuffer> &ib);

    private:
        unsigned int                               rendererID_;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
        std::shared_ptr<IndexBuffer>               indexBuffer_;
    };
} // namespace Engine
