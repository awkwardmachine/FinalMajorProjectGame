//
// Created by Nil on 09/03/2026.
//

#include "Engine/Core/Logger.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Engine {
    Logger::Logger(const LogLevel logLevel) : logLevel_(logLevel) {}

    Logger::~Logger() { closeLogFile(); }

    Logger &Logger::Get() {
        static Logger instance;
        return instance;
    }

    void Logger::setLogLevel(const LogLevel logLevel) {
        std::lock_guard lock(mutex_);
        logLevel_ = logLevel;
    }

    LogLevel Logger::getLogLevel() const {
        std::lock_guard lock(mutex_);
        return logLevel_;
    }

    void Logger::muteCategory(const std::string &category) {
        std::lock_guard lock(mutex_);
        mutedCategories_.insert(category);
    }

    void Logger::unmuteCategory(const std::string &category) {
        std::lock_guard lock(mutex_);
        mutedCategories_.erase(category);
    }

    bool Logger::isCategoryMuted(const std::string &category) const {
        std::lock_guard lock(mutex_);
        return mutedCategories_.contains(category);
    }

    void Logger::clearMutedCategories() {
        std::lock_guard lock(mutex_);
        mutedCategories_.clear();
    }

    void Logger::setLogFile(const std::string &path) {
        std::lock_guard lock(mutex_);
        if (logFile_.is_open())
            logFile_.close();
        logFile_.open(path, std::ios::out | std::ios::trunc);
    }

    void Logger::closeLogFile() {
        std::lock_guard lock(mutex_);
        if (logFile_.is_open())
            logFile_.close();
    }

    void Logger::flush() {
        std::lock_guard lock(mutex_);
        if (logFile_.is_open())
            logFile_.flush();
        std::cout.flush();
        std::cerr.flush();
    }

    void Logger::log(const std::string &message, const LogLevel logLevel, const char *category, const char *file,
                     const int line) {
        std::unique_lock lock(mutex_);

        if (logLevel != LogLevel::Fatal) {
            if (logLevel < logLevel_)
                return;
            if (category && mutedCategories_.contains(category))
                return;
        }

        std::string levelTag;
        switch (logLevel) {
            case LogLevel::Debug:
                levelTag = "[DEBUG]";
                break;
            case LogLevel::Info:
                levelTag = "[INFO]";
                break;
            case LogLevel::Warning:
                levelTag = "[WARNING]";
                break;
            case LogLevel::Error:
                levelTag = "[ERROR]";
                break;
            case LogLevel::Fatal:
                levelTag = "[FATAL]";
                break;
        }

        std::string categoryTag;
        if (category)
            categoryTag = std::string("[") + category + "] ";

        std::string location;
        if (file)
            location = " (" + std::string(file) + ":" + std::to_string(line) + ")";

        const std::string formatted = getTimestamp_() + " " + levelTag + " " + categoryTag + message + location;

        output_(formatted, logLevel);

        if (logLevel == LogLevel::Fatal) {
            if (logFile_.is_open())
                logFile_.flush();
            lock.unlock();
            std::_Exit(EXIT_FAILURE);
        }
    }

    std::string Logger::getTimestamp_() {
        using namespace std::chrono;
        const auto        now   = system_clock::now();
        const std::time_t now_c = system_clock::to_time_t(now);
        std::tm           local_tm{};
        localtime_s(&local_tm, &now_c);

        std::ostringstream oss;
        oss << std::put_time(&local_tm, "%d/%m/%Y %H:%M:%S");
        return oss.str();
    }

    void Logger::output_(const std::string &formattedMessage, const LogLevel logLevel) {
        if (logFile_.is_open()) {
            logFile_ << formattedMessage << "\n";
            logFile_.flush();
        }

        const char *color;
        switch (logLevel) {
            case LogLevel::Debug:
                color = "\033[34m";
                break;
            case LogLevel::Info:
                color = "\033[32m";
                break;
            case LogLevel::Warning:
                color = "\033[33m";
                break;
            case LogLevel::Error:
                color = "\033[31m";
                break;
            case LogLevel::Fatal:
                color = "\033[35m";
                break;
            default:
                color = "\033[0m";
                break;
        }
        constexpr auto reset = "\033[0m";

        auto &stream = (logLevel >= LogLevel::Error) ? std::cerr : std::cout;
        stream << color << formattedMessage << reset << "\n";
        stream.flush();
    }
} // namespace Engine
