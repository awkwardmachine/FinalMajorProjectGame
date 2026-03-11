//
// Created by Nil on 10/03/2026.
//

#include "Engine/Core/Application.h"
#include <chrono>
#include <glad/glad.h>
#include "Engine/Core/Logger.h"
#include "Engine/Renderer/Api/RendererFactory.h"

namespace Engine {
    Application::Application(Game &game) :
        game_(game), window_(game.settings_.title, game.settings_.width, game.settings_.height) {}

    bool Application::run() {
        if (!window_.init()) {
            LOG_ERROR_C("Engine", "Failed to initialize window.");
            return false;
        }
        // Create a window

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            LOG_ERROR_C("Engine", "Failed to initialize GLAD.");
            return false;
        }
        LOG_INFO_C("Engine", "Initialized GLAD.");

        // Enable VSync based on settings
        glfwSwapInterval(game_.settings_.vsyncEnabled ? 1 : 0);

        // Create the renderer
        const auto renderer = RendererFactory::createRenderer(game_.settings_.renderer);
        if (!renderer->init()) {
            LOG_ERROR_C("Engine", "Failed to initialize renderer.");
            return false;
        }
        renderer->setViewport(game_.settings_.width, game_.settings_.height);

        game_.renderer_ = renderer.get();

        game_.onStart(); // Call the game onStart

        auto lastTime = std::chrono::high_resolution_clock::now();

        // Main game loop
        while (!window_.shouldClose()) {
            window_.pollEvents();

            renderer->clear();

            // Update game logic per frame
            const auto  now       = std::chrono::high_resolution_clock::now();
            const float deltaTime = std::chrono::duration<float>(now - lastTime).count();
            lastTime              = now;
            game_.onUpdate(deltaTime);

            renderer->draw();

            window_.swapBuffers();
        }

        // Logic on shutdown
        game_.onShutdown();
        game_.renderer_ = nullptr;
        return true;
    }
} // namespace Engine
