#include <thetime/once_in.hpp>
#include <thetime/clock.hpp>

#include "test_clock.hpp"

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

using namespace igloo;
using namespace the::time;


Describe( once_in )
{

  void SetUp()
  {
    test_clock.reset( new test::Clock );
    oncein.reset( new the::time::OnceIn< test::Clock >( *test_clock, interval ) );
  }

  bool did_run_after( const the::time::Time& interval )
  {
    bool was_run{ false };
    test_clock->sleep_for( interval );
    oncein->run(
        [ &was_run ]()
        {
          was_run = true;
        } );
    return was_run;
  }

  It( does_not_run_the_given_code_block_until_interval_time_passes )
  {
    AssertThat( did_run_after( interval - 1 ), Equals( false ) );
  }

  It( runs_the_given_code_block_after_interval_time )
  {
    AssertThat( did_run_after( interval ), Equals( true ) );
    AssertThat( did_run_after( interval ), Equals( true ) );
  }

 // void tick_after( test::Clock::Time time )
 // {
 //   test_clock->sleep_for( time );
 //   frequency_meter->tick();
 // }

 // It( should_measure_the_frequency_of_ticks )
 // {
 //   tick_after( test::Clock::ticks_per_second );
 //   AssertThat( frequency_meter->per_second(), EqualsWithDelta( 1.0, 0.1 ) );

 //   const test::Clock::Time sixty_per_second_interval{ 16667u };
 //   tick_after( sixty_per_second_interval );
 //   AssertThat( frequency_meter->per_second(), EqualsWithDelta( 60.0, 0.1 ) );
 // }

 // void check_interval_after( test::Clock::Time time )
 // {
 //   tick_after( time );
 //   AssertThat( frequency_meter->interval(), Equals( time ) );
 // }

 // It( should_measure_interval_between_ticks )
 // {
 //   check_interval_after( test::Clock::Time( 100 ) );
 //   check_interval_after( test::Clock::Time( 101 ) );
 // }

 // It( works_with_thetime_clock )
 // {
 //   Clock real_clock;
 //   FrequencyMeter< Clock > fm( real_clock );
 //   fm.tick();
 //   fm.per_second();
 //   fm.interval();
 // }

  std::unique_ptr< test::Clock > test_clock;
  std::unique_ptr< OnceIn< test::Clock > > oncein;
  const the::time::Time interval{ 10000 };
};

