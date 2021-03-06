# required for igloo:
add_definitions(-Wno-deprecated-declarations)
include_directories(igloo)

set(TEST_SOURCE_FILES
    test_runner.cpp
    test_measurement.cpp
    test_clock.cpp
    test_frequency_meter.cpp
    test_frequency_stabilizer.cpp
    test_once_in.cpp
    )


add_executable(test_runner EXCLUDE_FROM_ALL ${TEST_SOURCE_FILES})
target_link_libraries(test_runner thetime ${LIBS})

get_target_property(TEST_RUNNER_BIN test_runner LOCATION) # for running


find_program( VALGRIND_PATH valgrind )

if(VALGRIND_PATH)
  set(RUNNER
    valgrind --leak-check=full --show-reachable=yes --log-file="valgrind.log"
    )
endif()

add_custom_target(test DEPENDS test_runner)
add_custom_command(TARGET test COMMAND ${RUNNER} ${TEST_RUNNER_BIN} --verbose DEPENDS test_runner)
