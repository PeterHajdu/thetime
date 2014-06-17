
set(SOURCE_FILES
  clock.cpp
    )

add_library(thetime STATIC ${SOURCE_FILES})
target_link_libraries(thetime ${LIBS})
install(TARGETS thetime DESTINATION lib)

