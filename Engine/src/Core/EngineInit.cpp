#include "Engine/Core/EngineInit.h"
#include "Engine/Core/Logger.h"

#include <csignal>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Engine {
    static std::string gLogFilePath;

    // Exits safely when a crash has occured
    static void logCrashAndExit(const std::string &reason) {
        const std::string suffix = gLogFilePath.empty() ? "No log file configured." : "See log file: " + gLogFilePath;
        Logger::Get().log("Crash caught: " + reason + ". " + suffix, LogLevel::Error, "Crash", __FILE__, __LINE__);

        Logger::Get().flush();
        std::_Exit(EXIT_FAILURE);
    }

    // Handles crashes and logs them
    static void crashHandler(const int signal) {
        std::string sigName;
        switch (signal) {
            case SIGABRT:
                sigName = "SIGABRT (abort)";
                break;
            case SIGSEGV:
                sigName = "SIGSEGV (segfault)";
                break;
            case SIGILL:
                sigName = "SIGILL (illegal instruction)";
                break;
            case SIGFPE:
                sigName = "SIGFPE (floating point error)";
                break;
            default:
                sigName = "Unknown signal (" + std::to_string(signal) + ")";
                break;
        }
        logCrashAndExit(sigName);
    }

#ifdef _WIN32
    static LONG WINAPI windowsExceptionHandler(EXCEPTION_POINTERS *info) {
        std::string reason;
        switch (info->ExceptionRecord->ExceptionCode) {
            case EXCEPTION_ACCESS_VIOLATION:
                reason = "Access violation (null/bad pointer)";
                break;
            case EXCEPTION_STACK_OVERFLOW:
                reason = "Stack overflow";
                break;
            case STATUS_HEAP_CORRUPTION:
                reason = "Heap corruption (use-after-free?)";
                break;
            case EXCEPTION_ILLEGAL_INSTRUCTION:
                reason = "Illegal instruction";
                break;
            case EXCEPTION_INT_DIVIDE_BY_ZERO:
                reason = "Integer divide by zero";
                break;
            default:
                char buf[16];
                snprintf(buf, sizeof(buf), "%08lX", info->ExceptionRecord->ExceptionCode);
                reason = "Windows exception 0x" + std::string(buf);
                break;
        }
        logCrashAndExit(reason);
        return EXCEPTION_EXECUTE_HANDLER;
    }
#endif

    static void registerCrashHandlers() {
        std::signal(SIGABRT, crashHandler);
        std::signal(SIGSEGV, crashHandler);
        std::signal(SIGILL, crashHandler);
        std::signal(SIGFPE, crashHandler);

#ifdef _WIN32
        SetUnhandledExceptionFilter(windowsExceptionHandler);
#endif
    }


    void EngineInit::Init(const EngineConfig &config) {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif

#ifdef NDEBUG
        Logger::Get().setLogLevel(LogLevel::Error);
        Logger::Get().muteCategory("Engine");
        gLogFilePath = config.logFile.empty() ? "engine.log" : config.logFile;
        Logger::Get().setLogFile(gLogFilePath);
#else
        Logger::Get().setLogLevel(config.logLevel);
        if (!config.logFile.empty()) {
            gLogFilePath = config.logFile;
            Logger::Get().setLogFile(gLogFilePath);
        }
#endif

        registerCrashHandlers();

#ifdef _WIN32
        if (config.showConsole) {
            for (DWORD handleId: {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE}) {
                HANDLE h = GetStdHandle(handleId);
                if (h != INVALID_HANDLE_VALUE) {
                    DWORD dwMode = 0;
                    if (GetConsoleMode(h, &dwMode)) {
                        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                        SetConsoleMode(h, dwMode);
                    }
                }
            }
        } else {
            FreeConsole();
        }
#endif

        LOG_INFO_C("Engine", "Engine initialised");
    }
} // namespace Engine
