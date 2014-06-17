# thetime

thetime is a simple time measurement library written in c++.

# Usage

## Generate simple output:

```c++
#include <thetime/timer.hpp>
using namespace the::time;

//...

measure(
  []()
  {
    //something to be measured
  } ).report_to( std::cout );
```

## Comparison

```c++
#include <thetime/time.hpp>
using namespace the::time;

//...

measure(
  []()
  {
    //something to be measured
  } ).took_less_than( std::chrono::microseconds( 50 ) );

measure(
  []()
  {
    //something to be measured
  } ).took_more_than( std::chrono::microseconds( 50 ) );
```

took_less_than and took_more_than functions return with bool to use it in your favourite ut framework.
If you need to combine more tests just take the result and play with it.

```c++
auto result(
  measure(
    []()
    {
      //something to be measured
    } ).took_more_than( std::chrono::microseconds( 50 ) ) );
result.took_more_than( std::chrono::microseconds( 50 ) );

//or just take the duration
result.duration();
```

## Misc
The library contains a helper class for repeated measurements. You can combine it with the measurement
framework.

```c++
//to repeat a call 10 times
10_times(
  []()
  {
    //this block is executed 10 times
  }
);
```

