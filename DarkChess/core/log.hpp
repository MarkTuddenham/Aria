#pragma once

#include <memory>
#include <unordered_map>

#include "spdlog/spdlog.h"

namespace DarkChess
{

class Log
{

public:
    enum Level
    {
        CRITICAL,
        ERROR,
        WARN,
        INFO,
        TRACE,
        NONE
    };

    static void init();
    static void init(const Log::Level &);

    inline static std::shared_ptr<spdlog::logger> &get_core_logger() { return s_core_logger; }
    inline static std::shared_ptr<spdlog::logger> &get_client_logger() { return s_client_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;

    static spdlog::level::level_enum dc_to_spdlog_level(Log::Level);
};

} // namespace DarkChess

#ifdef DEBUG
// Core Macros
#define DC_CORE_TRACE(...) ::DarkChess::Log::get_core_logger()->trace(__VA_ARGS__)
#define DC_CORE_INFO(...) ::DarkChess::Log::get_core_logger()->info(__VA_ARGS__)
#define DC_CORE_WARN(...) ::DarkChess::Log::get_core_logger()->warn(__VA_ARGS__)
#define DC_CORE_ERROR(...) ::DarkChess::Log::get_core_logger()->error(__VA_ARGS__)
#define DC_CORE_CRITICAL(...) ::DarkChess::Log::get_core_logger()->critical(__VA_ARGS__)
#else
// Core Macros
#define DC_CORE_TRACE(...)
#define DC_CORE_INFO(...)
#define DC_CORE_WARN(...)
#define DC_CORE_ERROR(...)
#define DC_CORE_CRITICAL(...)
#endif // DEBUG
