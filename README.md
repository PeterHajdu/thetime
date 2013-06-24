# libtimer

libtimer is a simple time measurement library written in c++.

# Usage

## Generate simple output:

```c++
#include <timer/Timer.hpp>
using namespace timer;

//...

measure(
  []()
  {
    //something to be measured
  } ).reportTo( std::cout );
```

## Comparison

```c++
#include <timer/Timer.hpp>
using namespace timer;

//...

measure(
  []()
  {
    //something to be measured
  } ).tookLessThan( std::chrono::microseconds( 50 ) );

measure(
  []()
  {
    //something to be measured
  } ).tookMoreThan( std::chrono::microseconds( 50 ) );
```

tookLessThan and tookMoreThan functions return with bool to use it in your favourite ut framework.
If you need to combine more tests just take the result and play with it.

```c++
auto result(
  measure(
    []()
    {
      //something to be measured
    } ).tookMoreThan( std::chrono::microseconds( 50 ) ) );
result.tookMoreThan( std::chrono::microseconds( 50 ) );

//or just take the duration
result.duration();
```

## Misc
The library contains a helper class for repeated measurements. You can combine it with the
with the measurement framework.

```c++
//to repeat a call 10 times
10_times(
  []()
  {
    //this block is executed 10 times
  }
);
```

