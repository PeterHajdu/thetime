#pragma once

namespace the
{
namespace time
{

template < typename Clock >
class FrequencyMeter
{
  public:
    typedef typename Clock::Time Time;
    FrequencyMeter( const Clock& clock )
      : m_clock( clock )
      , m_last_tick( 0 )
      , m_last_interval( 0 )
    {
    }

    void tick()
    {
      const Time now( m_clock.now() );
      m_last_interval = now - m_last_tick;
      m_last_tick = now;
    }

    float per_second() const
    {
      return Clock::ticks_per_second * 1.0 / m_last_interval;
    }

    Time interval() const
    {
      return m_last_interval;
    }

  private:
    const Clock& m_clock;
    Time m_last_tick;
    Time m_last_interval;
};

}
}

