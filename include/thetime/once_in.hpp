#pragma once

#include <thetime/clock.hpp>
#include <functional>

namespace the
{
namespace time
{

template < typename Clock >
class OnceIn
{
  public:
    using Callback = std::function< void( const Time& ) >;
    OnceIn( const Clock& clock, const Time& interval, Callback&& callback )
      : m_clock( clock )
      , m_interval( interval )
      , m_last_run( 0 )
      , m_callback( callback )
    {
    }

    void tick()
    {
      const Time now( m_clock.now() );
      if ( now - m_last_run < m_interval )
      {
        return;
      }

      m_last_run = now;
      m_callback( now );
    }

  private:
    const Clock& m_clock;
    const Time m_interval;
    Time m_last_run;
    Callback m_callback;
};

}
}

