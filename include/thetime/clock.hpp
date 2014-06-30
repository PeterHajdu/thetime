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
    static const Time ticks_per_second{ 1000000u };

    Clock();
    Time now() const;
    void set_time( const Time& time );

  private:
    typedef std::chrono::steady_clock InternalClockType;
    std::chrono::time_point< InternalClockType > m_start;

    typedef std::int64_t Offset;
    Offset m_offset;
};

}
}

