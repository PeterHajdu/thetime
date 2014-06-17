#include <thetime/clock.hpp>
#include <chrono>

the::time::Clock::Clock()
  : m_start( InternalClockType::now() )
{
}

the::time::Clock::Time
the::time::Clock::now() const
{
  std::chrono::microseconds delta( std::chrono::duration_cast< std::chrono::microseconds >(
        InternalClockType::now() - m_start ) );
  return delta.count();
}

