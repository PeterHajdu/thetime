#pragma once

#include <cstdint>
#include <chrono>

namespace the
{
namespace time
{

class Clock
{
  public:
    typedef std::uint64_t Time;
    static const Time tick_per_second{ 1000000u };

    Clock();
    Time now() const;

  private:
    typedef std::chrono::steady_clock InternalClockType;
    std::chrono::time_point< InternalClockType > m_start;
};

}
}

