#pragma once

#include <memory>
#include <unordered_map>

#include "spdlog/spdlog.h"

namespace Aria
{

class Log
{

public:
    enum Level
    {
        CRITICAL,
        ERR,
        WARN,
        INFO,
        TRACE,
        NONE
    };

    static void init();
    static void init(const Log::Level&);

    inline static std::shared_ptr<spdlog::logger> &get_core_logger() { return s_core_logger; }
    inline static std::shared_ptr<spdlog::logger> &get_client_logger() { return s_client_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;

    static spdlog::level::level_enum dc_to_spdlog_level(Log::Level);
};

} // namespace Aria

#ifdef DEBUG
// Core Macros
#define ARIA_CORE_TRACE(...) ::Aria::Log::get_core_logger()->trace(__VA_ARGS__)
#define ARIA_CORE_INFO(...) ::Aria::Log::get_core_logger()->info(__VA_ARGS__)
#define ARIA_CORE_WARN(...) ::Aria::Log::get_core_logger()->warn(__VA_ARGS__)
#define ARIA_CORE_ERROR(...) ::Aria::Log::get_core_logger()->error(__VA_ARGS__)
#define ARIA_CORE_CRITICAL(...) ::Aria::Log::get_core_logger()->critical(__VA_ARGS__)
#else
// Core Macros
#define ARIA_CORE_TRACE(...)
#define ARIA_CORE_INFO(...)
#define ARIA_CORE_WARN(...)
#define ARIA_CORE_ERROR(...)
#define ARIA_CORE_CRITICAL(...)
#endif // DEBUG
