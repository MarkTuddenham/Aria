#pragma once

#include <chrono>

namespace DarkChess::time
{

class Timer
{
public:
    Timer(const char*);
    ~Timer();
    void stop();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_point;
	const char* m_name;
	bool m_stopped;
};

} // namespace DarkChess::time