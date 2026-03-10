//
// Created by Nil on 10/03/2026.
//

#pragma once

#include "Engine/Core/DLLExports.h"

#include <string>

namespace Engine {
    struct ENGINE_API GameSettings {
        int         width        = 800;
        int         height       = 600;
        std::string title        = "Game";
        bool        vsyncEnabled = true;
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

    private:
        friend class Application;

        GameSettings settings_;
    };
} // namespace Engine
