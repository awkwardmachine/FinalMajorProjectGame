//
// Created by Nil on 10/03/2026.
//

#include "Engine/Core/Application.h"
#include "Engine/Core/Logger.h"

namespace Engine {
    Application::Application(Game &game) :
        game_(game), window_(game.settings_.title, game.settings_.width, game.settings_.height) {}

    bool Application::run() {
        if (!window_.init()) {
            LOG_ERROR_C("Engine", "Failed to initialize window.");
            return false;
        }
        // Create a window

        // Enable VSync based on settings
        glfwSwapInterval(game_.settings_.vsyncEnabled ? 1 : 0);

        game_.onStart(); // Call the game onStart

        auto lastTime = std::chrono::high_resolution_clock::now();

        // Main game loop
        while (!window_.shouldClose()) {
            window_.pollEvents();

            // Update game logic per frame
            const auto  now       = std::chrono::high_resolution_clock::now();
            const float deltaTime = std::chrono::duration<float>(now - lastTime).count();
            lastTime              = now;
            game_.onUpdate(deltaTime);

            window_.swapBuffers();
        }

        // Logic on shutdown
        game_.onShutdown();
        return true;
    }
} // namespace Engine
