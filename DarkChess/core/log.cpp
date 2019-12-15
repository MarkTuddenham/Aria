#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "DarkChess/core/log.hpp"

namespace DarkChess
{

std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::init() { Log::init(Log::Level::INFO); }
void Log::init(const Log::Level &level)
{

    spdlog::set_pattern("[%T] %^%l (%n): %v%$");

    const spdlog::level::level_enum spdlog_level = Log::dc_to_spdlog_level(level);

    s_core_logger = spdlog::stdout_color_mt("DarkChess Engine");
    s_core_logger->set_level(spdlog_level);

    s_client_logger = spdlog::stdout_color_mt("App");
    s_client_logger->set_level(spdlog_level);
}

spdlog::level::level_enum Log::dc_to_spdlog_level(Log::Level level)
{
    static const auto map = std::unordered_map<const Log::Level, const spdlog::level::level_enum>(
        {{Log::Level::CRITICAL, spdlog::level::critical},
         {Log::Level::ERROR, spdlog::level::err},
         {Log::Level::WARN, spdlog::level::warn},
         {Log::Level::INFO, spdlog::level::info},
         {Log::Level::TRACE, spdlog::level::trace},
         {Log::Level::NONE, spdlog::level::off}});

    return map.at(level);
}

} // namespace DarkChess
