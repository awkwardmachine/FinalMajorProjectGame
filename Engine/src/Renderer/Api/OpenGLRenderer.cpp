//
// Created by Nil on 10/03/2026.
//

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Engine/Core/Logger.h"
#include "Engine/Renderer/Api/OpenGLRenderer.h"

namespace Engine {
    bool OpenGLRenderer::init() {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            LOG_ERROR_C("Engine", "Failed to initialize glad.");
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Create a basic cube
        // Layout per vertex: x, y, z, u, v
        constexpr float vertices[] = {
                // back face
                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
                0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                0.0f,
                0.5f,
                0.5f,
                -0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                1.0f,

                // front face
                -0.5f,
                -0.5f,
                0.5f,
                0.0f,
                0.0f,
                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                0.0f,
                0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                0.5f,
                0.0f,
                1.0f,

                // left face
                -0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                1.0f,
                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
                -0.5f,
                -0.5f,
                0.5f,
                1.0f,
                0.0f,

                // right face
                0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,
                0.5f,
                0.5f,
                -0.5f,
                0.0f,
                1.0f,
                0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                0.0f,

                // bottom face
                -0.5f,
                -0.5f,
                -0.5f,
                0.0f,
                0.0f,
                0.5f,
                -0.5f,
                -0.5f,
                1.0f,
                0.0f,
                0.5f,
                -0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                -0.5f,
                0.5f,
                0.0f,
                1.0f,

                // top face
                -0.5f,
                0.5f,
                -0.5f,
                0.0f,
                0.0f,
                0.5f,
                0.5f,
                -0.5f,
                1.0f,
                0.0f,
                0.5f,
                0.5f,
                0.5f,
                1.0f,
                1.0f,
                -0.5f,
                0.5f,
                0.5f,
                0.0f,
                1.0f,
        };

        constexpr unsigned int indices[] = {
                0,  1,  2,  2,  3,  0, // back
                4,  5,  6,  6,  7,  4, // front
                8,  9,  10, 10, 11, 8, // left
                12, 13, 14, 14, 15, 12, // right
                16, 17, 18, 18, 19, 16, // bottom
                20, 21, 22, 22, 23, 20, // top
        };

        vertexArray_  = std::make_unique<VertexArray>();
        vertexBuffer_ = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        indexBuffer_  = std::make_unique<IndexBuffer>(indices, 36);

        vertexArray_->bind();
        vertexBuffer_->bind();
        indexBuffer_->bind();

        constexpr int stride = 5 * sizeof(float);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        vertexBuffer_->unbind();
        vertexArray_->unbind();

        shader_ = std::make_unique<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");
        if (!shader_->isValid()) {
            LOG_ERROR_C("Engine", "Shader failed to compile.");
            return false;
        }

        shader_->bind();
        shader_->setInt("uTexture", 0);
        shader_->unbind();

        TextureSettings pixelSettings;
        pixelSettings.minFilter = TextureFilter::Nearest;
        pixelSettings.magFilter = TextureFilter::Nearest;
        pixelSettings.mipMaps   = false;

        texture_ = std::make_unique<Texture>("textures/rock.png", pixelSettings);
        if (!texture_->isValid()) {
            LOG_ERROR_C("Engine", "Texture failed to load.");
        }

        return true;
    }

    void OpenGLRenderer::setViewProjection(const glm::mat4 &view, const glm::mat4 &projection) {
        view_       = view;
        projection_ = projection;
    }

    void OpenGLRenderer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void OpenGLRenderer::draw() {
        if (texture_ && texture_->isValid())
            texture_->bind(0);

        shader_->bind();

        constexpr auto model = glm::mat4(1.0f);
        shader_->setMat4Raw("uModel", glm::value_ptr(model));
        shader_->setMat4Raw("uView", glm::value_ptr(view_));
        shader_->setMat4Raw("uProjection", glm::value_ptr(projection_));

        vertexArray_->bind();
        indexBuffer_->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexBuffer_->getCount()), GL_UNSIGNED_INT, nullptr);
        vertexArray_->unbind();

        shader_->unbind();
    }

    void OpenGLRenderer::setViewport(const int width, const int height) { glViewport(0, 0, width, height); }
} // namespace Engine
