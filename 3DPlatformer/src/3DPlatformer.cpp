//
// Created by Nil on 10/03/2026.
//

#include "3DPlatformer.h"

#include <Engine/Core/Logger.h>

Platformer::Platformer() : Game({.width = 800, .height = 600, .title = "3D Platformer"}) {}

void Platformer::onStart() { LOG_INFO_C("Platformer", "Game started!"); }

void Platformer::onUpdate(float /*deltaTime*/) {}

void Platformer::onShutdown() {}
