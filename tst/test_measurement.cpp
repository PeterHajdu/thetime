#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>
#include <timer/Timer.hpp>
#include <thread>
using namespace igloo;
using namespace timer;

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

    AssertThat( result.tookLessThan( std::chrono::seconds( 1 ) ), Equals( false ) );
    AssertThat( result.tookLessThan( std::chrono::seconds( 3 ) ), Equals( true ) );
    AssertThat( result.tookMoreThan( std::chrono::seconds( 1 ) ), Equals( true ) );
    AssertThat( result.tookMoreThan( std::chrono::seconds( 3 ) ), Equals( false ) );
  }


  It( writes_report_to_an_ostream )
  {
    std::stringstream reportStream;
    measure(
        []()
        {
        }).report( reportStream );
    AssertThat( reportStream.str().empty(), Equals( false ) );
    AssertThat( reportStream.str(), Contains( "measurement took: " ) );
  }


  It( can_return_the_exact_measured_duration )
  {
    Result::StoredDurationType duration(
      measure(
          []()
          {
          }).duration() );
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
    AssertThat( counter, Equals( 10 ) );
  }
};

