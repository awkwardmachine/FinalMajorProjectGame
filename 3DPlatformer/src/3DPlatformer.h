//
// Created by Nil on 10/03/2026.
//

#pragma once

#include <Engine/Core/Game.h>

class Platformer : public Engine::Game {
public:
    Platformer();

protected:
    void onStart() override;
    void onUpdate(float deltaTime) override;
    void onShutdown() override;
};
