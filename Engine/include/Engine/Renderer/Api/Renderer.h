#pragma once

#include <glm/glm.hpp>

#include "Engine/Core/DLLExports.h"

namespace Engine {
    class ENGINE_API Renderer {
    public:
        virtual ~Renderer() = default;

        virtual bool init()                                                                = 0;
        virtual void clear()                                                               = 0;
        virtual void draw()                                                                = 0;
        virtual void setViewport(int width, int height)                                    = 0;
        virtual void setViewProjection(const glm::mat4 &view, const glm::mat4 &projection) = 0;
    };

} // namespace Engine
