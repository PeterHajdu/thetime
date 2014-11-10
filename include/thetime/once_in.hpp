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
    OnceIn( const Clock& clock, const Time& interval )
      : m_clock( clock )
      , m_interval( interval )
      , m_last_run( 0 )
    {
    }

    void run( std::function< void() > code )
    {
      const Time now( m_clock.now() );
      if ( now - m_last_run < m_interval )
      {
        return;
      }

      m_last_run = now;
      code();
    }

  private:
    const Clock& m_clock;
    const Time m_interval;
    Time m_last_run;
};

}
}

