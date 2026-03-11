//
// Created by Nil on 06/03/2026.
//

#include <iostream>

#include "Engine/Renderer/Api/OpenGLRenderer.h"
#include "Engine/Renderer/Api/RendererFactory.h"

namespace Engine {
    std::unique_ptr<Renderer> RendererFactory::createRenderer(const RendererAPI api) {
        switch (api) {
            case RendererAPI::OpenGL:
                return std::make_unique<OpenGLRenderer>();
            default:
                std::cerr << "Unknown RendererAPI, defaulting to OpenGL" << std::endl;
                return std::make_unique<OpenGLRenderer>();
        }
    }
} // namespace Engine
