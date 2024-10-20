# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tasks/task1)
# # add_executable(hello_world hello_world.cpp test_name1.cpp)
# # target_link_libraries(hello_world gtest gtest_main)
# add_executable(hello_world hello_world_test.cpp hello_world.cpp)
# target_link_libraries(hello_world gtest gtest_main)
# add_test(HWt hello_world_test COMMAND hello_world)

# Task executable
add_executable(exec_hello_world hello_world.cpp)
set_target_properties(exec_hello_world PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tasks/task1)

# Test executable
add_executable(test_hello_world test_hello_world.cpp)
target_link_libraries(test_hello_world gtest gtest_main)
set_target_properties(test_hello_world PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tasks/task1)

# Add test to CMake
add_test(HWt test_hello_world COMMAND test_hello_world)

