#pragma once

#include <cstdint>
#include <chrono>

namespace the
{
namespace time
{

class Clock
{
    typedef std::int64_t Offset;
  public:
    typedef std::uint64_t Time;
    static const Time ticks_per_second{ 1000000u };

    Clock();
    Time now() const;
    void set_time( const Time& time );
    void set_offset( const Offset& offset );

  private:
    typedef std::chrono::steady_clock InternalClockType;
    std::chrono::time_point< InternalClockType > m_start;

    Offset m_offset;
};

}
}

