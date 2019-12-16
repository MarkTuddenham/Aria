#pragma once

//  For use by Aria Applications

#include "Aria/config.hpp"

#include "Aria/core/board.hpp"
#include "Aria/core/fen.hpp"
#include "Aria/core/instrumentation.hpp"
#include "Aria/core/log.hpp"
#include "Aria/core/piece.hpp"
#include "Aria/core/utils.hpp"

#ifdef DEBUG
// Client Logging Macros
#define ARIA_TRACE(...) ::Aria::Log::get_client_logger()->trace(__VA_ARGS__)
#define ARIA_INFO(...) ::Aria::Log::get_client_logger()->info(__VA_ARGS__)
#define ARIA_WARN(...) ::Aria::Log::get_client_logger()->warn(__VA_ARGS__)
#define ARIA_ERROR(...) ::Aria::Log::get_client_logger()->error(__VA_ARGS__)
#define ARIA_CRITICAL(...) ::Aria::Log::get_client_logger()->critical(__VA_ARGS__)
#else
// Client Logging Macros
#define ARIA_TRACE(...)
#define ARIA_INFO(...)
#define ARIA_WARN(...)
#define ARIA_ERROR(...)
#define ARIA_CRITICAL(...)
#endif // DEBUG
