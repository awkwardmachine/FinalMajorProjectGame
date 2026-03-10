//
// Created by Nil on 09/03/2026.
//

#include <Engine/Core/EngineInit.h>
#include <Engine/Core/Logger.h>
#include <Engine/Platform/Window.h>
#include <iostream>

int main() {
    // Initialize the engine
    Engine::Logger::Get().muteCategory("Engine"); // You can mute categories to supress certain sections of messages
    Engine::EngineInit::Init({.logLevel = Engine::LogLevel::Debug, .showConsole = true, .logFile = "test.log"});

    LOG_INFO_C("Game", "Game starting..."); // Log game starting message in the Game category

    // Create a window with a title of "Hello Game Engine" and a
    // window width of 800 and height of 600
    Engine::Window window("Hello Game Engine", 800, 600);
    // If the window init method returns false, it produces an error
    if (!window.init()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }

    // Run this loop if the window shouldn't close keeping the window open
    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}
