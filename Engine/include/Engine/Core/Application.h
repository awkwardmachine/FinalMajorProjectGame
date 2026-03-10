//
// Created by Nil on 10/03/2026.
//

#pragma once

#include "Engine/Core/DLLExports.h"
#include "Engine/Core/Game.h"
#include "Engine/Platform/Window.h"

namespace Engine {
    class ENGINE_API Application {
    public:
        explicit Application(Game &game);
        [[nodiscard]] bool run();

    private:
        Game  &game_;
        Window window_;
    };
} // namespace Engine
