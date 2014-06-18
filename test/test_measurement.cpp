#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>
#include <thetime/timer.hpp>
#include <thread>
using namespace igloo;
using namespace the::time;

Describe( measurement )
{

  It( should_execute_given_code_block )
  {
    bool executed( false );
    measure(
        [ &executed ]()
        {
          executed = true;
        });
    AssertThat( executed, Equals( true ) );
  }


  It( can_check_time_limits )
  {
    auto result(
        measure(
        []()
        {
          std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
        } ) );

    AssertThat( result.took_less_than( std::chrono::seconds( 1 ) ), Equals( false ) );
    AssertThat( result.took_less_than( std::chrono::seconds( 3 ) ), Equals( true ) );
    AssertThat( result.took_more_than( std::chrono::seconds( 1 ) ), Equals( true ) );
    AssertThat( result.took_more_than( std::chrono::seconds( 3 ) ), Equals( false ) );
  }


  It( writes_report_to_an_ostream )
  {
    std::stringstream report_stream;
    measure(
        []()
        {
        }).report_to( report_stream );
    AssertThat(report_stream .str().empty(), Equals( false ) );
    AssertThat(report_stream .str(), Contains( "measurement took: " ) );
  }


  It( can_return_the_exact_measured_duration )
  {
    measure(
        []()
        {
        }).duration();
  }

};

Describe( repeater )
{
  It( executes_a_function_n_times )
  {
    size_t counter( 0 );
    10_times(
        [ &counter ]()
        {
          ++counter;
        } );
    AssertThat( counter, Equals( 10u ) );
  }
};

