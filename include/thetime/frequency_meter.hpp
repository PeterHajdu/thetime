#pragma once

namespace the
{
namespace time
{

template < typename Clock >
class FrequencyMeter
{
  public:
    FrequencyMeter( const Clock& clock )
      : m_clock( clock )
      , m_last_tick( 0 )
      , m_last_interval( 0.0 )
    {
    }

    void tick()
    {
      const typename Clock::Time now( m_clock.now() );
      m_last_interval = now - m_last_tick;
      m_last_tick = now;
    }

    float per_second() const
    {
      return Clock::tick_per_second * 1.0 / m_last_interval;
    }

  private:
    const Clock& m_clock;
    typename Clock::Time m_last_tick;
    typename Clock::Time m_last_interval;
};

}
}

