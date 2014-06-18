#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <thetime/frequency_meter.hpp>
#include <thread>

#include "test_clock.hpp"

using namespace igloo;
using namespace the::time;


Describe( frequency_meter )
{

  void SetUp()
  {
    test_clock.reset( new test::Clock );
    frequency_meter.reset( new FrequencyMeter< test::Clock >( *test_clock ) );
    frequency_meter->tick();
  }

  void tick_after( test::Clock::Time time )
  {
    test_clock->sleep_for( time );
    frequency_meter->tick();
  }

  It( should_measure_the_frequency_of_ticks )
  {
    tick_after( test::Clock::tick_per_second );
    AssertThat( frequency_meter->per_second(), EqualsWithDelta( 1.0, 0.1 ) );

    const test::Clock::Time sixty_per_second_interval{ 16667u };
    tick_after( sixty_per_second_interval );
    AssertThat( frequency_meter->per_second(), EqualsWithDelta( 60.0, 0.1 ) );
  }

  std::unique_ptr< test::Clock > test_clock;
  std::unique_ptr< FrequencyMeter< test::Clock > > frequency_meter;
};

