# Task executable
add_executable(exec_what_is_a_set what_is_a_set.cpp)
set_target_properties(exec_what_is_a_set PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tasks_hash_tables/task1_what_is_a_set)

# Test executable
add_executable(test_what_is_a_set test_what_is_a_set.cpp)
target_link_libraries(test_what_is_a_set gtest gtest_main)
set_target_properties(test_what_is_a_set PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tasks_hash_tables/task1_what_is_a_set)

# Add test to CMake
add_test(HWt test_what_is_a_set COMMAND test_what_is_a_set)

