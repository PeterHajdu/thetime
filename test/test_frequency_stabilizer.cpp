#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <thetime/frequency_stabilizer.hpp>
#include "test_clock.hpp"

using namespace igloo;
using namespace the::time;

namespace
{
  class TestSleeper
  {
    public:
      void operator()( const test::Clock::Time& duration ) const
      {
        slept_for = duration;
      }

      static void reset()
      {
        slept_for = 0;
      }

      static test::Clock::Time slept_for;
  };

  test::Clock::Time TestSleeper::slept_for{ 0 };
}

Describe( a_frequency_stabilizer )
{
  template< int frequency, test::Clock::Time delay  >
  void test_sleep_interval_for_frequency_after()
  {
    FrequencyStabilizer< frequency, test::Clock, TestSleeper > frequency_stabilizer( test_clock );
    test_clock.sleep_for( delay );
    frequency_stabilizer.stabilize();

    const test::Clock::Time expected_sleep_time( test::Clock::ticks_per_second / frequency - delay );
    AssertThat( TestSleeper::slept_for, EqualsWithDelta( expected_sleep_time, 1 ) );
  }

  It( sleeps_for_the_right_interval_to_achieve_frequency )
  {
    test_sleep_interval_for_frequency_after<60, 1000>();
    test_sleep_interval_for_frequency_after<30, 1000>();
  }

  It( has_default_sleeper )
  {
    FrequencyStabilizer< 60, test::Clock > frequency_stabilizer( test_clock );
    frequency_stabilizer.stabilize();
  }

  test::Clock test_clock;
};

