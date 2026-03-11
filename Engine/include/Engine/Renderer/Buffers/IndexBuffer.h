#pragma once

#include <cstddef>

#include "Engine/Core/DLLExports.h"

namespace Engine {
    class ENGINE_API IndexBuffer {
    public:
        IndexBuffer(const unsigned int *indices, size_t count);
        ~IndexBuffer();
        void                       bind() const;
        void                       unbind() const;
        [[nodiscard]] unsigned int getCount() const { return count_; }

    private:
        unsigned int rendererID_;
        unsigned int count_;
    };
} // namespace Engine
