#pragma once

#include <chrono>

namespace pong::time
{
using namespace std::chrono_literals;

using Duration = std::chrono::microseconds;
using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock, Duration>;

inline TimePoint Now() noexcept
{
    return std::chrono::time_point_cast<Duration>(Clock::now());
}

constexpr float SecInFloat(const Duration& value) noexcept
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1, 1>>>(value).count();
}

}
