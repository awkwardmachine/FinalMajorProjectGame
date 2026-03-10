//
// Created by Nil on 09/03/2026.
//

#pragma once

#include "Engine/Core/DLLExports.h"

#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <unordered_set>

namespace Engine {
    enum class LogLevel { Debug, Info, Warning, Error, Fatal };

    class ENGINE_API Logger {
    public:
        void log(const std::string &message, LogLevel logLevel, const char *category = nullptr,
                 const char *file = nullptr, int line = 0);

        void     setLogLevel(LogLevel logLevel);
        LogLevel getLogLevel() const;

        void muteCategory(const std::string &category);
        void unmuteCategory(const std::string &category);
        bool isCategoryMuted(const std::string &category) const;
        void clearMutedCategories();

        void setLogFile(const std::string &path);
        void closeLogFile();
        void flush();

        static Logger &Get();

    private:
        explicit Logger(LogLevel logLevel = LogLevel::Info);
        ~Logger();

        LogLevel                        logLevel_;
        std::unordered_set<std::string> mutedCategories_;
        std::ofstream                   logFile_;
        mutable std::mutex              mutex_;

        std::string getTimestamp_();
        void        output_(const std::string &formattedMessage, LogLevel logLevel);
    };

#define LOG_DEBUG(msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Debug, nullptr, __FILE__, __LINE__)
#define LOG_INFO(msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Info, nullptr, __FILE__, __LINE__)
#define LOG_WARN(msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Warning, nullptr, __FILE__, __LINE__)
#define LOG_ERROR(msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Error, nullptr, __FILE__, __LINE__)
#define LOG_FATAL(msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Fatal, nullptr, __FILE__, __LINE__)

#define LOG_DEBUG_C(cat, msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Debug, cat, __FILE__, __LINE__)
#define LOG_INFO_C(cat, msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Info, cat, __FILE__, __LINE__)
#define LOG_WARN_C(cat, msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Warning, cat, __FILE__, __LINE__)
#define LOG_ERROR_C(cat, msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Error, cat, __FILE__, __LINE__)
#define LOG_FATAL_C(cat, msg) Engine::Logger::Get().log(msg, Engine::LogLevel::Fatal, cat, __FILE__, __LINE__)

#define LOG_DEBUG_IF(cond, msg)                                                                                        \
    do {                                                                                                               \
        if (cond)                                                                                                      \
            LOG_DEBUG(msg);                                                                                            \
    } while (0)
#define LOG_INFO_IF(cond, msg)                                                                                         \
    do {                                                                                                               \
        if (cond)                                                                                                      \
            LOG_INFO(msg);                                                                                             \
    } while (0)
#define LOG_WARN_IF(cond, msg)                                                                                         \
    do {                                                                                                               \
        if (cond)                                                                                                      \
            LOG_WARN(msg);                                                                                             \
    } while (0)
#define LOG_ERROR_IF(cond, msg)                                                                                        \
    do {                                                                                                               \
        if (cond)                                                                                                      \
            LOG_ERROR(msg);                                                                                            \
    } while (0)
#define LOG_FATAL_IF(cond, msg)                                                                                        \
    do {                                                                                                               \
        if (cond)                                                                                                      \
            LOG_FATAL(msg);                                                                                            \
    } while (0)

#define ENGINE_ASSERT(cond, msg)                                                                                       \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            Engine::Logger::Get().log(std::string("Assertion failed: (" #cond ") -- ") + (msg),                        \
                                      Engine::LogLevel::Fatal, "Assert", __FILE__, __LINE__);                          \
        }                                                                                                              \
    } while (0)
} // namespace Engine
