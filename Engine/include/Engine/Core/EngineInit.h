#pragma once

#include "Engine/Core/DLLExports.h"
#include "Engine/Core/Logger.h"

#include <string>

namespace Engine {
    struct ENGINE_API EngineConfig {
        LogLevel logLevel    = LogLevel::Debug;
        bool     showConsole = true;

        std::string logFile;
    };

    class ENGINE_API EngineInit {
    public:
        static void Init(const EngineConfig &config = {});
    };
} // namespace Engine
