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
    oncein.reset( new the::time::OnceIn< test::Clock >(
          *test_clock,
          interval,
          [ &was_run = was_run, &last_called_at = last_called_at ]( const the::time::Time& timestamp )
          {
            last_called_at = timestamp;
            was_run = true;
          } ) );
  }

  bool did_run_after( const the::time::Time& interval )
  {
    was_run = false;
    test_clock->sleep_for( interval );
    oncein->tick();
    return was_run;
  }

  It( does_not_run_the_given_code_block_until_interval_time_passes )
  {
    AssertThat( did_run_after( interval - 1 ), Equals( false ) );
  }

  It( runs_the_given_code_block_after_interval_time )
  {
    AssertThat( did_run_after( interval ), Equals( true ) );
  }

  It( passes_the_current_time_to_the_callback_function )
  {
    AssertThat( did_run_after( interval ), Equals( true ) );
    AssertThat( last_called_at, Equals( test_clock->now() ) );
  }

  It( resets_the_timer_after_each_execution )
  {
    AssertThat( did_run_after( interval ), Equals( true ) );
    AssertThat( did_run_after( interval - 1 ), Equals( false ) );
  }

  bool was_run;
  std::unique_ptr< test::Clock > test_clock;
  std::unique_ptr< OnceIn< test::Clock > > oncein;
  const the::time::Time interval{ 10000 };
  the::time::Time last_called_at;
};

