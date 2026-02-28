file(GLOB SRC_TESTS "*.cpp")

include_directories(../gtest)
include_directories(../src)

add_executable(tests ${SRC_TESTS})
target_link_libraries(tests bst gtest)
