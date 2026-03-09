//
// Created by Nil on 09/03/2026.
//

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // Import GLFW library used to make the window

#include <string>

#include "Engine/Core/DLLExports.h" // Import engine symbols

namespace Engine {
    class ENGINE_API Window { // Create Window Class with public and private methods
    public:
        Window(std::string title, int width, int height);
        ~Window();

        // Convenience methods
        [[nodiscard]] std::string getTitle() const;
        [[nodiscard]] int         getWidth() const;
        [[nodiscard]] int         getHeight() const;
        [[nodiscard]] bool        shouldClose() const;

        // GLFW wrappers (abstraction layer)
        bool init();
        void pollEvents();
        void swapBuffers() const;
        void setTitle(const std::string &title);
        void resize(int width, int height);

        [[nodiscard]] GLFWwindow *getWindow() const;

    private: // Stored private variables local to the class
        GLFWwindow *window_{nullptr};
        std::string title_;
        int         width_, height_;
        bool        init_{false};
    };
} // namespace Engine
