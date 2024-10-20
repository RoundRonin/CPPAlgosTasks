add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world gtest gtest_main)
add_test(HWt hello_world_test COMMAND hello_world)
