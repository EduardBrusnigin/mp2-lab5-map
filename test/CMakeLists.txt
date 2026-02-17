file(GLOB SRC_TESTS "*.cpp")

include_directories(../include)
include_directories(../gtest)


add_executable(tests ${SRC_TESTS})
target_link_libraries(tests arithmetic gtest)
