//
// Created by Nil on 10/03/2026.
//

#include "Engine/Core/Game.h"

namespace Engine {
    Game::Game(GameSettings settings) : settings_(std::move(settings)) {}
} // namespace Engine
