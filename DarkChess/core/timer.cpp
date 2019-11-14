#include <chrono>

#include "DarkChess/core/timer.hpp"
#include "DarkChess/core/log.hpp"

namespace DarkChess::time
{

Timer::Timer(const char* t_name) : m_name(t_name), m_stopped(false)
{
    m_start_time_point = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	if (!m_stopped)
		stop();
}

void Timer::stop()
{
    auto end_time_point = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time_point).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration * 0.001;

	m_stopped = true;
	
	DC_CORE_INFO("{:.3f}ms | {}", ms, m_name);
}
} // namespace DarkChess::time