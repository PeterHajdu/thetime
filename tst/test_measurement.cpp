#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>
#include <timer/Timer.hpp>
using namespace igloo;
using namespace timer;

Describe( measurement )
{

  It( should_execute_given_code_block )
  {
    bool executed( false );
    measure()(
        [ &executed ]()
        {
          executed = true;
        });
    AssertThat( executed, Equals( true ) );
  }

};

