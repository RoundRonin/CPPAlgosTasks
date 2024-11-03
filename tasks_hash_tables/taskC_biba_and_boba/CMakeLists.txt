# Variable for the base name
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE "_" ";" PARTS ${PARENT_DIR})
list(LENGTH PARTS PARTS_LENGTH)
list(SUBLIST PARTS 0 1 TASK_NUMBER_LIST)
list(SUBLIST PARTS 1 ${PARTS_LENGTH} TASK_NAME_LIST)
list(JOIN TASK_NUMBER_LIST "" TASK_NUMBER)
list(JOIN TASK_NAME_LIST "_" TASK_NAME)

# Get the grandparent directory
get_filename_component(TASK_LEVEL ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(TASK_LEVEL ${TASK_LEVEL} NAME)

# Concatenate strings to form source files and executables
set(TASK_SRC main.cpp)
set(TEST_SRC test.cpp)
set(TASK_EXEC exec_${TASK_NAME})
set(TEST_EXEC test_${TASK_NAME})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/${TASK_LEVEL}/${TASK_NUMBER}_${TASK_NAME})

# Task executable
add_executable(${TASK_EXEC} ${SRC_DIR}/${TASK_SRC})
set_target_properties(${TASK_EXEC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SRC_DIR})

# Test executable
add_executable(${TEST_EXEC} ${SRC_DIR}/${TEST_SRC})
target_link_libraries(${TEST_EXEC} gtest gtest_main)
set_target_properties(${TEST_EXEC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SRC_DIR})

# Add test to CMake
add_test(HWt ${TEST_EXEC} COMMAND ${TEST_EXEC})
