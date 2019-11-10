#pragma once

//  For use by DarkChess Applications

#include "DarkChess/config.hpp"

#include "DarkChess/core/board.hpp"
#include "DarkChess/core/piece.hpp"
#include "DarkChess/core/utils.hpp"
#include "DarkChess/core/log.hpp"

// Client Logging Macros
#define DC_TRACE(...) ::DarkChess::Log::get_client_logger()->trace(__VA_ARGS__)
#define DC_INFO(...) ::DarkChess::Log::get_client_logger()->info(__VA_ARGS__)
#define DC_WARN(...) ::DarkChess::Log::get_client_logger()->warn(__VA_ARGS__)
#define DC_ERROR(...) ::DarkChess::Log::get_client_logger()->error(__VA_ARGS__)
#define DC_FATAL(...) ::DarkChess::Log::get_client_logger()->fatal(__VA_ARGS__)
