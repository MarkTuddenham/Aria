// #include <iostrea
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "DarkChess/core/log.hpp"

namespace DarkChess
{

std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::init()
{
    spdlog::set_pattern("[%T] %^(%n %l) %v%$");

    s_core_logger = spdlog::stdout_color_mt("DarkChess Engine");
    s_core_logger->set_level(spdlog::level::trace);

    s_client_logger = spdlog::stdout_color_mt("App");
    s_client_logger->set_level(spdlog::level::trace);
}

} // namespace DarkChess