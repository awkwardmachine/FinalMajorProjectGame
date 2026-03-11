//
// Created by Nil on 10/03/2026.
//

#pragma once

#include "Engine/Core/DLLExports.h"
#include "Engine/Renderer/Api/Renderer.h"
#include "Engine/Renderer/Api/RendererFactory.h"

#include <string>

namespace Engine {
    struct ENGINE_API GameSettings {
        int         width        = 800;
        int         height       = 600;
        std::string title        = "Game";
        bool        vsyncEnabled = true;
        RendererAPI renderer     = RendererAPI::OpenGL;
    };

    class ENGINE_API Game {
    public:
        explicit Game(GameSettings settings = {});
        virtual ~Game() = default;

        Game(const Game &)            = delete;
        Game &operator=(const Game &) = delete;

    protected:
        virtual void onStart() {}
        virtual void onUpdate(float deltaTime) {}
        virtual void onShutdown() {}

        Renderer *renderer_ = nullptr;

    private:
        friend class Application;

        GameSettings settings_;
    };
} // namespace Engine
