#include <thetime/clock.hpp>
#include <chrono>

the::time::Clock::Clock()
  : m_start( InternalClockType::now() )
  , m_offset( 0 )
{
}


the::time::Clock::Time
the::time::Clock::now() const
{
  std::chrono::microseconds delta( std::chrono::duration_cast< std::chrono::microseconds >(
        InternalClockType::now() - m_start ) );
  return delta.count() + m_offset;
}


void
the::time::Clock::set_time( const Time& time )
{
  m_offset = time - now();
}

