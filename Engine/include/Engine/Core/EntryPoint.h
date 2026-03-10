//
// Created by Nil on 10/03/2026.
//

#pragma once

#include "Engine/Core/Application.h"
#include "Engine/Core/Game.h"

namespace Engine {
    inline int engineRun(Game &game) {
        Application engine(game);
        return engine.run() ? 0 : -1;
    }
} // namespace Engine
