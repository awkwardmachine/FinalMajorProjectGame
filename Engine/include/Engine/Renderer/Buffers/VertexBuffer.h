#pragma once

#include <cstddef>

#include "Engine/Core/DLLExports.h"

namespace Engine {
    class ENGINE_API VertexBuffer {
    public:
        VertexBuffer(const void *data, size_t size);
        ~VertexBuffer();
        void bind() const;
        void unbind() const;
        void setData(const void *data, size_t size) const;

    private:
        unsigned int rendererID_;
    };
} // namespace Engine
