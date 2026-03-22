file(GLOB SRC_TESTS "*.cpp")
list(REMOVE_ITEM SRC_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp")

include_directories(../gtest)
include_directories(../src)

add_executable(tests ${SRC_TESTS})
add_executable(sample sample.cpp)
target_link_libraries(tests gtest)
