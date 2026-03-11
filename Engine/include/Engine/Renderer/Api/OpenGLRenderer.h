#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Engine/Core/DLLExports.h"
#include "Engine/Renderer/Api/Renderer.h"
#include "Engine/Renderer/Buffers/IndexBuffer.h"
#include "Engine/Renderer/Buffers/VertexArray.h"
#include "Engine/Renderer/Buffers/VertexBuffer.h"
#include "Engine/Renderer/Resources/Shader.h"
#include "Engine/Renderer/Resources/Texture.h"

namespace Engine {
    class ENGINE_API OpenGLRenderer : public Renderer {
    public:
        bool init() override;
        void clear() override;
        void draw() override;
        void setViewport(int width, int height) override;
        void setViewProjection(const glm::mat4 &view, const glm::mat4 &projection) override;

    private:
        std::unique_ptr<Shader>       shader_;
        std::unique_ptr<Texture>      texture_;
        std::unique_ptr<VertexArray>  vertexArray_;
        std::unique_ptr<VertexBuffer> vertexBuffer_;
        std::unique_ptr<IndexBuffer>  indexBuffer_;

        glm::mat4 view_       = glm::mat4(1.0f);
        glm::mat4 projection_ = glm::mat4(1.0f);
    };
} // namespace Engine
