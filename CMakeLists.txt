cmake_minimum_required(VERSION 3.10)
project(SGDB)

set(CMAKE_CXX_STANDARD 17)

# Establish the build type to be Release by default if not specified by the user
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

# Include the gtest library
add_subdirectory(googletest)

# Include the headers from the project
include_directories(${PROJECT_SOURCE_DIR}/include) 

add_executable(sgdb_test 
    tests/test_database.cpp 
    tests/test_table.cpp 
    tests/test_index.cpp
    src/database.cpp 
    src/table.cpp 
    src/index.cpp)

# Link the gtest library to the test executable
target_link_libraries(sgdb_test gtest gtest_main)

# Enable testing for the project and add the test executable
enable_testing()
add_test(NAME SGDBTests COMMAND sgdb_test)
