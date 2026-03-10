//
// Created by Nil on 09/03/2026.
//

#include <Engine/Core/EngineInit.h>
#include <Engine/Core/EntryPoint.h>

#include "3DPlatformer.h"

int main() {
    Engine::EngineInit::Init({.logLevel = Engine::LogLevel::Debug, .showConsole = true, .logFile = "test.log"});

    Platformer platformer;
    return Engine::engineRun(platformer);
}
