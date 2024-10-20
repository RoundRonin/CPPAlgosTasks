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
add_subdirectory(tasks)
add_subdirectory(tasks_hash_tables)
