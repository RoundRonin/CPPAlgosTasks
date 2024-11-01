cmake_minimum_required(VERSION 3.10)
project(Tasks)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Add tasks
# add_subdirectory(tasks)
# add_subdirectory(tasks_hash_tables)

file(GLOB TASK_DIRS RELATIVE ${CMAKE_SOURCE_DIR} tasks*)
foreach(TASK_DIR ${TASK_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${TASK_DIR})
        add_subdirectory(${TASK_DIR})
    endif()
endforeach()
