#pragma once

#include <memory>

#include "Engine/Core/DLLExports.h"
#include "Engine/Renderer/Api/Renderer.h"

namespace Engine {
    enum class RendererAPI { OpenGL };

    class ENGINE_API RendererFactory {
    public:
        static std::unique_ptr<Renderer> createRenderer(RendererAPI api);
    };
} // namespace Engine
