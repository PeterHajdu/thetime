#include <igloo/igloo_alt.h>
using namespace igloo;

#include <thetime/clock.hpp>
#include <type_traits>
#include <thread>
#include <chrono>

Describe( a_clock )
{
  template < typename Time >
  struct TimeTypeCheck
  {
    TimeTypeCheck() {};
    static_assert( std::is_integral< Time >::value, "Type of time should be an integral type." );
    static_assert( ! std::is_signed< Time >::value, "Type of time should be unsigned." );
    static_assert( std::numeric_limits< Time >::digits == 64, "Type of time should have size of 64 bits." );
  };

  It ( should_define_an_unsigned_64_bit_time_type )
  {
    typedef the::time::Clock::Time TimeType;
    TimeTypeCheck< TimeType > check;
  }

  It ( should_return_Time_Type_from_now_function )
  {
    typedef decltype( test_clock.now() ) TimeType;
    TimeTypeCheck< TimeType > check;
  }

  void check_clock_setting( int64_t offset )
  {
    the::time::Clock::Time start( test_clock.now() );
    const the::time::Clock::Time expected_time( start + offset );
    test_clock.set_clock( expected_time );
    AssertThat( test_clock.now(), EqualsWithDelta( expected_time, std::abs( offset ) * 0.01 ) );
  }

  It ( should_be_possible_to_set_the_clock_back )
  {
    check_clock_setting( 2000000 );
  }

  It ( should_be_possible_to_set_the_clock_forward )
  {
    check_clock_setting( -2000000 );
  }

  It ( should_have_at_least_microsec_precision )
  {
    the::time::Clock::Time t0( test_clock.now() );
    std::this_thread::sleep_for( std::chrono::microseconds( 1 ) );
    the::time::Clock::Time t1( test_clock.now() );
    AssertThat( t1, Is().GreaterThan( t0 ) );
  }

  the::time::Clock test_clock;
};

