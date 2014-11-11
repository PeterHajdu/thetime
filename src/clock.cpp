#include <thetime/clock.hpp>
#include <chrono>

const the::time::Time the::time::Clock::ticks_per_second{ 1000000u };

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

void
the::time::Clock::set_offset( const Offset& offset )
{
  m_offset = offset;
}

