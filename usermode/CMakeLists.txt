cmake_minimum_required(VERSION 3.10)
project(KernelModule VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# Specify the directories for output and object files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Collect all source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(KernelModule ${SOURCES})

# Test binary
add_executable(poc_test tests/test_main.cpp)
target_link_libraries(poc_test PRIVATE gtest_main GTest::GTest GTest::Main Threads::Threads)

# Register test
include(GoogleTest)
gtest_discover_tests(poc_test)
