/**
 * Copyright (c) 2013 Peter Ferenc Hajdu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **/

#pragma once
#include <chrono>

namespace timer
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


      void report( std::ostream& output )
      {
        output << "measurement took: " << m_measuredDuration.count() << " microseconds";
      }


      template < class DurationType >
      bool tookLessThan( DurationType durationLimit )
      {
        return m_measuredDuration < durationLimit;
      }


      template < class DurationType >
      bool tookMoreThan( DurationType durationLimit )
      {
        return m_measuredDuration > durationLimit;
      }

    private:
      const StoredDurationType m_measuredDuration;
  };


  class Measurement
  {
    public:
      typedef std::chrono::steady_clock Clock;


      Result operator()( std::function< void() > code )
      {
        Clock::time_point start( Clock::now() );
        code();
        return Result( std::chrono::duration_cast< Result::StoredDurationType >( Clock::now() - start ) );
      }
  };


  Measurement measure()
  {
    return Measurement();
  }
}

