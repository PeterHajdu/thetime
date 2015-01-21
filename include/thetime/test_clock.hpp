#pragma once

namespace test
{

class Clock
{
  public:
    typedef std::uint64_t Time;
    static const Time ticks_per_second{ 1000000u };

    Clock()
      : m_time( 0 )
    {
    }

    void sleep_for( const Time& time )
    {
      m_time += time;
    }

    Time now() const
    {
      return m_time;
    }

  private:
    Time m_time;
};

}

