//
// Created by Nil on 09/03/2026.
//

#include "Engine/Platform/Window.h"

namespace Engine {
    Window::Window(std::string title, const int width, const int height) :
        title_(std::move(title)), width_(width), height_(height) {} // This constructs the window

    bool Window::init() { // This is run to create the window itself
        if (!glfwInit()) {
            init_ = false;
            // TODO ADD LOG MESSAGE FOR FAILED INIT GLFW
            return false;
        }

        window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
        // This creates the window through GLFW
        if (!window_) {
            init_ = false;
            // TODO ADD LOG MESSAGE FOR FAILED CREATE GLFW WINDOW
            return false;
        }

        glfwMakeContextCurrent(window_);
        // This makes the window the current context in the OS
        // TODO ADD LOG MESSAGE FOR INIT WINDOW
        init_ = true;
        return true; // Returns true when the window is created successfully
    }

    void Window::setTitle(const std::string &title) {
        title_ = title;
        glfwSetWindowTitle(window_, title_.c_str());
    }

    std::string Window::getTitle() const { return title_; }

    int Window::getWidth() const { return width_; }

    int Window::getHeight() const { return height_; }

    void Window::resize(const int width, const int height) {
        width_  = width;
        height_ = height;
        glfwSetWindowSize(window_, width_, height_);
    }

    void Window::swapBuffers() const { glfwSwapBuffers(window_); }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void Window::pollEvents() { glfwPollEvents(); }

    GLFWwindow *Window::getWindow() const { return window_; }

    bool Window::shouldClose() const { return glfwWindowShouldClose(window_); }

    Window::~Window() {
        if (window_) {
            glfwDestroyWindow(window_);
            window_ = nullptr;
            // TODO LOG WINDOW DESTROYED
        }
        glfwTerminate();
    }

} // namespace Engine
