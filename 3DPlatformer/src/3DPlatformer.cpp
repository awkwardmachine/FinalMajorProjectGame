//
// Created by Nil on 10/03/2026.
//

#include "3DPlatformer.h"

#include <Engine/Core/Logger.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Platformer::Platformer() :
    Game({.width = 800, .height = 600, .title = "3D Platformer", .renderer = Engine::RendererAPI::OpenGL}) {}

void Platformer::onStart() {
    LOG_DEBUG_C("Platformer", "Game started!");

    if (renderer_) {
        const glm::mat4 view =
                glm::lookAt(glm::vec3(0.0f, 1.5f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        const glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        renderer_->setViewProjection(view, projection);
    }
}

void Platformer::onUpdate(float /*deltaTime*/) {}

void Platformer::onShutdown() {}
