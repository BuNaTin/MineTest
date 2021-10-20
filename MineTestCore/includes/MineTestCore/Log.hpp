
#pragma once

#include <spdlog/spdlog.h>

namespace MineTest {

#ifdef NDEBUG

#define CONSOLE_LOG_INFO(...) 
#define CONSOLE_LOG_WARN(...) 
#define CONSOLE_LOG_ERROR(...) 
#define CONSOLE_LOG_CRITICAL(...) 

#else // DEBUG

#define CONSOLE_LOG_INFO(...)  spdlog::info(__VA_ARGS__)
#define CONSOLE_LOG_WARN(...)  spdlog::warn(__VA_ARGS__)
#define CONSOLE_LOG_ERROR(...)  spdlog::error(__VA_ARGS__)
#define CONSOLE_LOG_CRITICAL(...)  spdlog::critical(__VA_ARGS__)

#endif

}