#pragma once
#include <thetime/frequency_meter.hpp>
#include <thread>
#include <chrono>

namespace the
{
namespace time
{

template < typename Clock >
class SimpleSleeper
{
  public:
    void operator()( const typename Clock::Time& duration_in_microseconds ) const
    {
      std::this_thread::sleep_for( std::chrono::microseconds(
           duration_in_microseconds ) );
    }
};

template < int Frequency, typename Clock, typename Sleeper = SimpleSleeper< Clock > >
class FrequencyStabilizer
{
  public:
    typedef typename Clock::Time Time;
    const int frequency = Frequency;
    const Time ticks_per_second = Clock::ticks_per_second;
    const Time ticks_per_period = Clock::ticks_per_second / frequency;

    FrequencyStabilizer( const Clock& clock )
      : m_frequecy_meter( clock )
    {
      m_frequecy_meter.tick();
    }

    void stabilize()
    {
      m_frequecy_meter.tick();
      m_sleep( ticks_per_period - m_frequecy_meter.interval() );
      m_frequecy_meter.tick();
    }

  private:
    FrequencyMeter< Clock > m_frequecy_meter;
    Sleeper m_sleep;
};

}
}

