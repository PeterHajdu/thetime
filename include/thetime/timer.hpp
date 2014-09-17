#pragma once
#include <chrono>
#include <ostream>
#include <functional>

namespace the
{
namespace time
{

  class Result
  {
    public:
      typedef std::chrono::microseconds StoredDurationType;

      template < class DurationType >
      Result( const DurationType& measuredDuration )
        : m_measuredDuration( measuredDuration )
      {
      }


      void report_to( std::ostream& output )
      {
        output << "measurement took: "
               << m_measuredDuration.count()
               << " microseconds"
               << std::endl;
      }


      template < class DurationType >
      bool took_less_than( DurationType durationLimit )
      {
        return m_measuredDuration < durationLimit;
      }


      template < class DurationType >
      bool took_more_than( DurationType durationLimit )
      {
        return m_measuredDuration > durationLimit;
      }


      const StoredDurationType& duration() const
      {
        return m_measuredDuration;
      }

    private:
      const StoredDurationType m_measuredDuration;
  };


  inline Result measure( std::function< void() > code )
  {
    typedef std::chrono::steady_clock Clock;
    Clock::time_point start( Clock::now() );
    code();
    return Result( std::chrono::duration_cast< Result::StoredDurationType >( Clock::now() - start ) );
  }


  class Repeater
  {
    public:
      typedef unsigned long long int CounterType;
      Repeater( const CounterType& count )
        : m_count( count )
      {
      }

      void operator()( std::function< void() > code )
      {
        for ( CounterType i( 0 ); i < m_count; ++i )
        {
          code();
        }
      }

    private:
      const CounterType m_count;
  };

}
}

the::time::Repeater operator "" _times( the::time::Repeater::CounterType count )
{
  return the::time::Repeater( count );
}

